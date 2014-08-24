compile:
	gcc -std=c99 -o sbfi sbfi.c

test_s:
	gcc -std=c99 -o sbfi sbfi.c
	./sbfi -s test.bf

test_a:
	gcc -std=c99 -o sbfi sbfi.c
	./sbfi -a test.bf
	
test_c:
	gcc -std=c99 -o sbfi sbfi.c
	./sbfi -a test.bf
