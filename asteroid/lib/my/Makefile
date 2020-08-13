##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## My makefile
##

SOURCE	=	*.c \
			lld/*.c \
			csfml/*.c \
			#mat/*.c \
			#ucp/*.c \
			#btr/*.c \

OBJ		=	$(SOURCE:.c=.o)

all:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/

build:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/

buildO4:
	gcc -c $(SOURCE) -Ofast
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/
	rm -f *.o

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f libmy.a
	rm -f ../libmy.a
	rm -f ../../include/*.h

re: clean all

valgrind: fclean
	gcc -g -c $(SOURCE) -Wall -Wextra
	ar rc libmy.a *.o
	cp libmy.a ../
	cp *.h ../../include/
	rm -f *.o
