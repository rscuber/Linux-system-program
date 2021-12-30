.PHONY: clean run
CC = gcc
all: main.o rstest/test.o rstest/test.h 
	$(CC) main.o rstest/test.o -o bin/rstest 
main.o: main.c rstest/test.h 
	gcc -I./ -c main.c -o main.o 
rstest/test.o: rstest/test.c rstest/test.h 
	gcc -I./ -c rstest/test.c -o rstest/test.o 
clean:
	rm -rf bin/rstest main.o rstest/test.o
run:
	./bin/rstest
