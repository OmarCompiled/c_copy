CC=gcc
CFLAGS=-Wall

copy: main.c copy.c utils.c
	${CC} ${CFLAGS} main.c copy.c utils.c -o copy

install: copy
	sudo cp copy /usr/bin

clean: copy
	rm ./copy

delete:
	sudo rm /usr/bin/copy
