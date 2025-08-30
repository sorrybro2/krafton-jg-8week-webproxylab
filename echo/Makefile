CC = gcc
CFLAGS = -O2 -Wall -I .
LIB = -lpthread

all: echoserver echoclient cgi

echoserver: echoserver.c echo.o csapp.o
	$(CC) $(CFLAGS) -o echoserver echoserver.c echo.o csapp.o $(LIB)

echoclient: echoclient.c csapp.o
	$(CC) $(CFLAGS) -o echoclient echoclient.c csapp.o $(LIB)

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

echo.o: echo.c csapp.h
	$(CC) $(CFLAGS) -c echo.c

cgi:
	(cd cgi-bin; make)

clean:
	rm -f *.o echoserver echoclient *~
	(cd cgi-bin; make clean)
