compile:
	gcc -std=c99 -o sbfi sbfi.c

teststep:
	gcc -std=c99 -o sbfi sbfi.c
	./sbfi -s test.bf

testall:
	gcc -std=c99 -o sbfi sbfi.c
	./sbfi -a test.bf
