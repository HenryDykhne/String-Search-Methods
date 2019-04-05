CFLAGS = -g -ggdb3 -Wall -std=c11 -pedantic -Iinclude

all: A3q1 A3q2

A3q1: A3q1.o A3.o
	gcc ${CFLAGS} A3q1.o A3.o -o A3q1

A3q2: A3q2.o A3.o
	gcc ${CFLAGS} A3q2.o A3.o -o A3q2



A3q1.o: A3q1.c
	gcc ${CFLAGS} A3q1.c -o A3q1.o -c

A3q2.o: A3q2.c
	gcc ${CFLAGS} A3q2.c -o A3q2.o -c
	


A3.o: A3.c
	gcc ${CFLAGS} A3.c -o A3.o -c
	


clean:
	rm *.o *.so core