CC = gcc

all: timer timer2
.PHONEY:clean  all

timer:timer.c
	$(CC) -o timer timer.c `pkg-config --cflags --libs gtk+-2.0`
timer2:timer2.c
	$(CC) -o timer2 timer2.c `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm timer timer2
