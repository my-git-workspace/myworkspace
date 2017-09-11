all:
	gcc -finstrument-functions -g -c -o main.o main.c
	gcc -finstrument-functions -g -c -o trace.o trace.c
	gcc main.o trace.o -o main
