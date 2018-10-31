# this is a comment

CC=gcc

dict1: dict1.o bst1.o
	$(CC) -o dict1 dict1.o bst1.o

bst1.o: bst1.c bst1.h
	$(CC) -c -Wall bst1.c

dict1.o: dict1.c dict1.h
	$(CC) -c -Wall dict1.c

dict2: dict2.o bst2.o
	$(CC) -ansi -o dict2 dict2.o bst2.o

bst2.o: bst2.c bst2.h
	$(CC) -c -Wall bst2.c

dict2.o: dict2.c dict2.h
	$(CC) -c -Wall dict2.c
