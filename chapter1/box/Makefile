CC = gcc
all:
	$(CC) -o box box.c `pkg-config --cflags --libs gtk+-2.0`
.PHONY:clean
clean:
	rm box
