LIBS= -ldl
CC=gcc
SRCS= example.c
OBJECTS=$(SRCS:.c=.o)
CFLAGS=-O9 -rdynamic

all: shared.so example

example: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

shared.so: shared.o
	ld -shared shared.o -o shared.so

clean:
	rm -f *.o core *~ example *.so
