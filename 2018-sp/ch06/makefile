SHELL = /bin/bash
CC = clang
CFLAGS = -g -lacl
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${EXE}
