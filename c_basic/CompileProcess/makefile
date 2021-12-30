.PHONY: run clean
test.i: test.c
	gcc -E $< -o $@
	# cpp test.c -o test.i
test.s: test.c
	gcc -S $< -o $@
test.o: test.s
	gcc -c $< -o $@
	# as test.s -o test.o
prog: test.o 
	gcc $< -o $@
clean:
	rm -f prog 
run:
	./prog
