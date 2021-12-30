CXX := g++
CFLAGS := -I./ -g -Og -std=c++14
LDFLAGS :=

all: task

task: task.cc meta.hh
	$(CXX) $(CFLAGS) $(LDFLAGS) task.cc -o task

run: task
	./task

.PHONY: clean

clean:
	-rm -fr task *~ *.o key.* letter

