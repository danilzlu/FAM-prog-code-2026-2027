CC ?= cc
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g -O0
LECTURE = lecture/floyd.c lecture/intlist.c lecture/tree.c
SEMINAR = seminar/exercises.c
.PHONY: all test clean
all: demo tests_runner
demo: lecture/demo.c $(LECTURE)
	$(CC) $(CFLAGS) $^ -o $@
tests_runner: tests/test.c $(LECTURE) $(SEMINAR)
	$(CC) $(CFLAGS) $^ -o $@
test: tests_runner
	./tests_runner
clean:
	rm -f demo tests_runner
