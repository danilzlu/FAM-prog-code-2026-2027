CC = cc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g -O0

.PHONY: all run clean
all: demo

demo: main.c search/search.c search/search.h sorting/sorting.c sorting/sorting.h list/list.c list/list.h
	$(CC) $(CFLAGS) main.c search/search.c sorting/sorting.c list/list.c -o $@

run: demo
	./demo

clean:
	rm -f demo
