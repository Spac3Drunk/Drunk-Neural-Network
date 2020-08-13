##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## My makefile
##

all:	build

build:
		gcc -Ofast -c *.c
		ar rc libevolve.a *.o
		cp libevolve.a ../
		cp evolve.h ../../include/
		rm -f *.o

clean:
		rm -f *.o

fclean:
		rm -f *.o
		rm -f libevolve.a
		rm -f ../libevolve.a
		rm -f ../../include/evolve.h

re: clean all

valgrind: fclean
		gcc -g -c *.c
		ar rc libevolve.a *.o
		cp libevolve.a ../
		cp evolve.h ../../include/
		rm -f *.o
