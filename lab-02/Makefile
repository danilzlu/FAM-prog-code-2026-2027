CC = gcc
CPPFLAGS = -Iinclude
WARNFLAGS = -Wall -Wextra -Wpedantic
SOURCES = src/main.c src/avlset.c
TARGET = avlset
.PHONY: all debug sanitize clean
all: $(TARGET)
$(TARGET): $(SOURCES) include/avlset.h
	$(CC) $(CPPFLAGS) $(WARNFLAGS) -std=c11 -O2 $(SOURCES) -o $(TARGET)
debug:
	$(CC) $(CPPFLAGS) $(WARNFLAGS) -std=c11 -O0 -g3 $(SOURCES) -o $(TARGET)
sanitize:
	$(CC) $(CPPFLAGS) $(WARNFLAGS) -std=c11 -O1 -g3 -fno-omit-frame-pointer -fsanitize=address,undefined $(SOURCES) -o $(TARGET)
clean:
	rm -f $(TARGET)
