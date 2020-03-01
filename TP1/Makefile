ALL = display_stack try_mul

compile: $(ALL)

try.o : try.c try.h
	gcc -c $<
	# pour compilation 32 bits
	# gcc -m32 -fno-pic -c $<
try_mul.o : try_mul.c try.h
	gcc -c $<
	# pour compilation 32 bits
	# gcc -m32 -fno-pic -c $<
try_mul: try_mul.o try.o
	gcc $^ -o $@
	# pour compilation 32 bits
	# gcc -m32 -fno-pic $^ -o $@
display_stack: display_stack.c
	gcc $^ -o $@

tryMul: try_mul
	./try_mul

displayStack: display_stack
	./display_stack

clean:
	rm -f *.o *.s $(ALL)
