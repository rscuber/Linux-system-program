CC = gcc 
CFLAGS = -std=c99
.PHONY: clean run
all:  libthread_pool.a server.o
	$(CC) $(CFLAGS) server.c -L./thread_pool -lthread_pool -lpthread -o echo_server
thread_pool.o: ./thread_pool/thread_pool.h ./thread_pool/thread_pool.c head.h
	$(CC) $(CFLAGS) -c thread_pool/thread_pool.c -o thread_pool/thread_pool.o
libthread_pool.a: ./thread_pool/thread_pool.o
	ar -crs ./thread_pool/libthread_pool.a ./thread_pool/thread_pool.o
run:
	./echo_server -p 8080
clean:
	rm server.o ./thread_pool/thread_pool.o ./thread_pool/libthread_pool.a echo_server

