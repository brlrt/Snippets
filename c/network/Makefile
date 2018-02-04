INCS		=	-I ..
CFLAGS		=	-O2 -Wall $(INCS) 
CC		=	gcc

all:
	make -C build build

initall:
	mkdir build
	cp Makefile build

clean:
	rm -f build/*.o server client udpserver daemon reaping *~

distclean:	clean
	rm -fr build

build:	server client udpserver daemon reaping

server:	server.o 
	$(CC) $(CFLAGS) $(INCS) -o ../server server.o

client: client.o
	$(CC) $(CFLAGS) $(INCS) -o ../client client.o

udpserver:	udpserver.o 
	$(CC) $(CFLAGS) $(INCS) -o ../udpserver udpserver.o

daemon:	daemon.o
	$(CC) $(CFLAGS) $(INCS) -o ../daemon daemon.o

reaping:	reaping.o
	$(CC) $(CFLAGS) $(INCS) -o ../reaping reaping.o

%.o:	../%.c 
	$(CC) $(CFLAGS) -c $<
