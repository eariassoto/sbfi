sbfi
====

Simple Brainfuck Interpreter
This is an interpreter for programs written in the esoteric language brainfuck.
If you want to learn more about this language you can visit http://es.wikipedia.org/wiki/Brainfuck

How to use: 
To compile the program you can use GCC both in Windows or Unix like OS. Compile as:
	gcc -std=c99 -o sbfi sbfi.c
Or you can use the Makefile.

To interpret a brainfuck program you have to run this program with the following arguments:

	./sfbi -[exec_option] name_of_file.bf \nWhere the options are:
	s -> Executes the program step by step, outputs console and memory.
	a -> Executes the program all at once, outputs console and memory.
	c -> Executes the program at once, outputs console only.

For example, try ./sbfi -s test.bf;
