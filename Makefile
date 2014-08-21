compile:
	gcc -std=c99 -o sbfc sbfc.c

teststep:
	gcc -std=c99 -o sbfc sbfc.c
	./sbfc -s test.bf

testall:
	gcc -std=c99 -o sbfc sbfc.c
	./sbfc -a test.bf
