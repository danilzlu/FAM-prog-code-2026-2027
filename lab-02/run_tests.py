#!/usr/bin/env python3
"""Run student avlset E2E tests. Requires only Python 3.9+ and GNU Make."""
import argparse
import difflib
import os
from pathlib import Path
import subprocess
import sys
import time

HERE=Path(__file__).resolve().parent
LEVELS=(4,6,8,9,10)

def parse():
    p=argparse.ArgumentParser(description='E2E tests for avlset (Linux/macOS/WSL)')
    p.add_argument('--level',type=int,choices=LEVELS,required=True)
    p.add_argument('--stress',action='store_true',help='include large performance tests')
    p.add_argument('--sanitize',action='store_true',help='build with make sanitize and check ASan/UBSan')
    p.add_argument('--timeout',type=float,default=3.0,help='seconds per ordinary test (default: 3)')
    p.add_argument('--stress-timeout',type=float,default=12.0,help='seconds per stress test (default: 12)')
    p.add_argument('--no-build',action='store_true',help='use existing executable')
    p.add_argument('--project',type=Path,default=Path.cwd(),help='project root containing Makefile')
    return p.parse_args()

def compare(expected,actual):
    e=expected.splitlines(); a=actual.splitlines()
    for i in range(max(len(e),len(a))):
        x=e[i] if i<len(e) else '<нет строки>'
        y=a[i] if i<len(a) else '<нет строки>'
        if x!=y: return f'строка ответа {i+1}: expected={x!r}, actual={y!r} (всего expected={len(e)}, actual={len(a)})'
    return None

def main():
    a=parse()
    if a.timeout<=0 or a.stress_timeout<=0: sys.exit('Лимит времени должен быть положительным')
    project=a.project.resolve(); exe=project/'avlset'
    if sys.platform=='win32': exe=project/'avlset.exe'
    if not a.no_build:
        cmd=['make','-B','sanitize' if a.sanitize else 'all']
        print('Сборка:', ' '.join(cmd),flush=True)
        try: result=subprocess.run(cmd,cwd=project,capture_output=True,text=True,errors='replace')
        except FileNotFoundError: sys.exit('Не найден make. Используйте Linux, WSL или macOS с GNU Make.')
        if result.returncode:
            print('FAIL: сборка не удалась\n'+result.stdout+result.stderr)
            return 2
    if not exe.is_file(): sys.exit(f'Исполняемый файл не найден: {exe}')
    cases=[]
    for f in sorted((HERE/'tests').glob('L*.in')):
        name=f.stem
        try: level=int(name.split('_')[0][1:])
        except ValueError: continue
        if level>a.level or ('_stress_' in name and not a.stress): continue
        cases.append(f)
    if not cases: sys.exit('Не найдены тесты')
    failures=0; total=0.0
    for f in cases:
        expected=f.with_suffix('.expected')
        if not expected.is_file():
            print(f'[FAIL] {f.stem}: отсутствует {expected.name}'); failures+=1; continue
        timeout=(a.stress_timeout if '_stress_' in f.stem else a.timeout)
        if a.sanitize: timeout*=3  # instrumented binaries are slower
        env=os.environ.copy()
        if a.sanitize and sys.platform.startswith('linux'):
            env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1:abort_on_error=1'
            env['UBSAN_OPTIONS']='halt_on_error=1:print_stacktrace=1'
        start=time.perf_counter()
        try:
            with f.open('rb') as stdin:
                r=subprocess.run([str(exe)],cwd=project,stdin=stdin,stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=timeout,env=env)
            elapsed=time.perf_counter()-start; total+=elapsed
            stderr=r.stderr.decode('utf-8','replace')
            actual=r.stdout.decode('utf-8','replace')
            want=expected.read_text(encoding='utf-8')
            reason=None
            if r.returncode!=0: reason=f'код завершения {r.returncode}; stderr: {stderr[:1200]!r}'
            elif a.sanitize and any(tag in stderr for tag in ('ERROR: AddressSanitizer','runtime error:','LeakSanitizer','SUMMARY: UndefinedBehaviorSanitizer')):
                reason='санитайзер: '+stderr[:1200]
            else: reason=compare(want,actual)
            if reason:
                failures+=1; print(f'[FAIL] {f.stem} ({elapsed:.3f} с): {reason}')
            else: print(f'[ OK ] {f.stem} ({elapsed:.3f} с)')
        except subprocess.TimeoutExpired:
            elapsed=time.perf_counter()-start; total+=elapsed; failures+=1
            print(f'[TIME] {f.stem}: превышен лимит {timeout:g} с')
        except OSError as e:
            failures+=1; print(f'[FAIL] {f.stem}: ошибка запуска: {e}')
    print(f'\nИтого: {len(cases)-failures}/{len(cases)} успешно; суммарное время запуска {total:.3f} с')
    if failures: print('Тесты не пройдены. Проверьте указанные случаи.')
    else: print('Все выбранные тесты пройдены (это не доказывает требуемую асимптотику).')
    return 1 if failures else 0

if __name__=='__main__': sys.exit(main())
