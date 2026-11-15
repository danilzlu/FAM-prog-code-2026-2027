#!/usr/bin/env python3
"""Проверка kvstore на публичных тестах (Python 3.10+, только стандартная библиотека)."""
from __future__ import annotations

import argparse
import difflib
import json
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path


def explain_bytes(expected: bytes, actual: bytes, *, file_name: str) -> str:
    if expected == actual:
        return ""
    if file_name == "stdout" or (b"\0" not in expected and b"\0" not in actual and
                                 all(byte < 128 for byte in expected[:512] + actual[:512])):
        before = expected.decode("utf-8", errors="replace").splitlines(keepends=True)
        after = actual.decode("utf-8", errors="replace").splitlines(keepends=True)
        difference = list(difflib.unified_diff(before, after,
                             fromfile="expected", tofile="actual", n=2))
        if difference:
            return "\n".join("    " + line.rstrip("\n") for line in difference[:24])
    # Бинарное представление для KVB1 или для нетекстовых данных.
    mismatch_at = next((i for i, (x,y) in enumerate(zip(expected, actual)) if x!=y),
                       min(len(expected), len(actual)))
    start = max(0, mismatch_at - 8)
    return (f"    first differing byte: {mismatch_at}; size {len(expected)} expected, {len(actual)} actual\n"
            f"    expected [{start}:{mismatch_at+16}]: {expected[start:mismatch_at+16].hex(' ')}\n"
            f"    actual   [{start}:{mismatch_at+16}]: {actual[start:mismatch_at+16].hex(' ')}")


def main() -> int:
    parser = argparse.ArgumentParser(description="Публичные тесты kvstore")
    parser.add_argument("executable", help="путь к скомпилированной программе kvstore")
    parser.add_argument("--levels", type=int, nargs="+", default=[4, 6, 8, 9, 10],
                        help="группы тестов, например --levels 4 6")
    parser.add_argument("--timeout", type=float, default=10, help="лимит секунд на один тест (по умолчанию 10)")
    parser.add_argument("--select", help="номер теста или часть названия")
    parser.add_argument("--verbose", action="store_true", help="показывать успешно пройденные тесты")
    args = parser.parse_args()

    if args.timeout <= 0:
        parser.error("--timeout должен быть больше нуля")
    exe = Path(args.executable).expanduser().resolve()
    if not exe.is_file():
        parser.error(f"файл программы не найден: {exe}")
    suite = Path(__file__).resolve().parent.parent / "tests"
    cases = json.loads((suite / "manifest.json").read_text(encoding="utf-8"))["cases"]
    chosen = [case for case in cases if case["level"] in args.levels and
              (not args.select or args.select in str(case["id"]) or args.select in case["name"])]
    if not chosen:
        parser.error("не найдено подходящих тестов")

    failed = 0
    counts: dict[int, list[int]] = {}
    print(f"kvstore: {exe}\nТестов выбрано: {len(chosen)}\n")
    for case in chosen:
        p = suite / case["directory"]
        problems = []
        elapsed = 0.0
        with tempfile.TemporaryDirectory(prefix="kvstore-public-") as tmp:
            work = Path(tmp)
            for item in p.iterdir():
                if item.name in {"commands.txt", "input.store", "output.store"}:
                    shutil.copyfile(item, work / item.name)
            start = time.monotonic()
            try:
                proc = subprocess.run([str(exe), *case["argv"]], cwd=work, stdin=subprocess.DEVNULL,
                                      stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                      timeout=args.timeout)
                elapsed = time.monotonic() - start
                if proc.returncode != case["exit_code"]:
                    problems.append(f"код завершения {proc.returncode}, ожидается {case['exit_code']}")
                expected_out = (p / "expected.stdout").read_bytes()
                if proc.stdout != expected_out:
                    problems.append("не совпадает stdout:\n" +
                                    explain_bytes(expected_out, proc.stdout, file_name="stdout"))
                if case["exit_code"] == 0 and proc.stderr:
                    problems.append(f"stderr должен быть пустым: {proc.stderr[:250]!r}")
                if case["exit_code"] != 0 and not proc.stderr:
                    problems.append("при ошибке необходимо сообщение в stderr")
                saved_path = case["save_path"]
                if saved_path:
                    saved = work / saved_path
                    if case["expect_saved_file"]:
                        expected_file = (p / "expected.store").read_bytes()
                        if not saved.is_file():
                            problems.append(f"не создан/сохранён файл {saved_path}")
                        elif saved.read_bytes() != expected_file:
                            problems.append(f"содержимое {saved_path} неверно:\n" +
                                            explain_bytes(expected_file, saved.read_bytes(), file_name=saved_path))
                    elif saved.exists():
                        problems.append(f"файл {saved_path} не должен быть создан")
            except subprocess.TimeoutExpired:
                elapsed = time.monotonic() - start
                problems.append(f"превышено время {args.timeout} с")
            except OSError as exc:
                elapsed = time.monotonic() - start
                problems.append(f"не удалось запустить программу: {exc}")
        counts.setdefault(case["level"], [0, 0])
        counts[case["level"]][0] += 1
        if problems:
            failed += 1
            print(f"FAIL  #{case['id']:03d}  уровень {case['level']}  {case['name']}")
            for issue in problems:
                print("  " + issue)
        else:
            counts[case["level"]][1] += 1
            if args.verbose:
                print(f"PASS  #{case['id']:03d}  уровень {case['level']}  {case['name']}  {elapsed:.3f} с")
    print("\nИтог по уровням:")
    for level, (total, passed) in sorted(counts.items()):
        print(f"  {level}/10: {passed}/{total}")
    print(f"Всего пройдено: {len(chosen)-failed}/{len(chosen)}")
    if failed:
        print("Важно: прохождение публичных тестов не гарантирует прохождения закрытых тестов.")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
