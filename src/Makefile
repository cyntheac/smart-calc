CC =gcc
CFLAGS =-Wall -Werror -Wextra -pedantic

all: build

build:
	$(CC) $(CFLAGS) main.c parser.c calculate.c translate.c stack.c main.h -o main

rebuild: clean all

clean: rm -rf main
