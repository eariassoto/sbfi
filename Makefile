compile:
	gcc -std=c99 -o build/sbfi sbfi.c

run:
	./build/sbfi -s examples/test.bf

test_s:
	gcc -std=c99 -o build/sbfi sbfi.c
	./build/sbfi -s examples/test.bf

test_a:
	gcc -std=c99 -o build/sbfi sbfi.c
	./build/sbfi -a examples/test.bf
	
test_c:
	gcc -std=c99 -o build/sbfi sbfi.c
	./build/sbfi -c examples/test.bf
