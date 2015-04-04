sbfi
====
Version 0.2

Simple Brainfuck Interpreter
This is an interpreter for programs written in brainfuck.
If you want to learn more about this language please visit http://es.wikipedia.org/wiki/Brainfuck.

Synopsis
-------------
 
	sbfi **OPTION** **NAME_OF_FILE**
    
Description:
-------------

	Run a Brainfuck program according to **OPTION**:
 	-s Executes step by step, outputs console and memory
	-a Executes all at once, outputs console and memory
	-c Executes all once, outputs console only

Changes:
-----------
0.2 4/4/15
* Fixed bug in cycles
* Eliminated redundant code
* Implemented bolded and colored text (for better reading in step by step mode)

TODO:
--------
* Syntax revision
* Overflow detection
* GUI
* Comment removing