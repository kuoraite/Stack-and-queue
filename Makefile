all: main.c
	gcc -c main.c stack.c queue.c -I.
	gcc main.o stack.o queue.o -o main.exe
	main.exe