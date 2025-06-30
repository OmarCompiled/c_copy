CC = gcc
CFLAGS = -Wall -std=c89
EXE = copy

copy : main.c
	${CC} ${CFLAGS} main.c type_check.c copy.c -o ${EXE}

delete: copy
	rm copy
