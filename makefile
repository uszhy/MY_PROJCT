CC=gcc
MAK=make -C
I=-I./include
L=-L./dongtai
export LD_LIBRARY_PATH=./dongtai
main:
	$(MAK) ./student/
	$(MAK) ./course/
	$(CC) main.c $(I) $(L) -lstudent -lcourse -o main

