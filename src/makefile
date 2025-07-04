CC = gcc
CFLAGS = -Wall -std=c89

copy: main.c copy.c type_check.c
	${CC} main.c copy.c type_check.c ${CFLAGS} -o copy

install: copy
	sudo cp copy /usr/bin

clean: copy
	rm ./copy

delete:
	sudo rm /usr/bin/copy
