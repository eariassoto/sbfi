/**
 * Simple Brainfuck Interpreter.
 * This program interprets programs written in the esoteric language
 * brainfuck. 
 * Between implementation options are executing the program step by step
 * or all the program at once.
 * 
 * @author Emmanuel Arias
 * 
 */
#if defined(_WIN32)
	static char *CLEAR = "cls";
#else
	static char *CLEAR = "clear";
#endif

#define KRESET "\033[0m"
#define KBOLD  "\033[1m"
#define KRED   "\x1B[31m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief type for the memory of the program 
 * 
 * 
 */
typedef char cell;

// Usually, the rules for compiling bf programs sets a maximum memory of 30000 bytes
static cell bf_memory[30000];
static cell *p, *last_p;

// We need this array in order to store the console output. Because we are simulating
// a "debugging" environment we need to store the output somewhere.
static char bf_console[30000];
static char *curr_c, *last_c;

enum EXEC_MODE {
   STEPS = 's',
   CONSOLE_MEMORY = 'a',
   CONSOLE_ONLY = 'c'
};

/**
 * @brief Prints the output of the program.
 * 
 * 
 */
void print_console(){
	char *c = &bf_console[0];
	while(c < last_c){
		printf("%c", *c);
		++c;
	}
	printf("\n");
}

/**
 * @brief Prints the memory used by the program.
 * 
 * 
 */
void print_memory(){
	printf(KBOLD"Memory Address\tValue\n"KRESET);
	cell *curr_p = &bf_memory[0];
	while(curr_p <= last_p){
		printf("%p\t%d", curr_p, *curr_p);
		if(curr_p == p)
			printf(KBOLD"\t* pointer is here"KRESET);
		printf("\n");
		++curr_p;
	}
	printf("\n");
}

/**
 * @brief Prints the bf program
 * @param input Stream with the bf file
 * 
 * 
 */
void print_instructions(FILE *input){
	char c;
	long pos = ftell(input); //save the current position
	fseek(input, 0, SEEK_SET);
	printf(KBOLD"Instructions:"KRESET"\n");
	while( (c = getc(input)) != EOF ){
		if(ftell(input) == pos+1){
			printf(KBOLD KRED"%c"KRESET,c);
		}else{
			printf("%c",c);
		}
	}
	fseek(input, pos, SEEK_SET); //restore the position
	printf("\n");
}

/**
 * @brief Checks if the character is a valid bf instruction
 * @param c Character to evaluate
 * @returns true if the character is an instruction
 * 
 * 
 */
int is_command(char c){
	return (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']');
}

/**
 * @brief Prints the entire program
 * @param command 
 * @param input 
 * 
 * 
 */
void print_program(char command, FILE *input){
	system(CLEAR);
	print_instructions(input);
	printf("\n" KBOLD "Console output:" KRESET "\n");
	
	print_console();
	printf("\n");
	
	if(is_command(command)){
		printf("Command executed: %c\n", command);
		printf("\n");
	}
	
	print_memory();
	printf("\n");
}

/**
 * @brief Executes one command
 * 
 * 
 */
void execute_command(char command, FILE *input){
	char c;
	long pos;

	switch(command) {
	case '>':
		++p;
		if(!*p)
			++last_p;
		break;
	case '<':
		--p;
		break;
	case '+':
		++*p;
		break;
	case '-':
		--*p;
		break;
	case '.':
		*curr_c = *p;
		++curr_c;
		++last_c;
		break;
	case ',':
		printf("Enter a character: ");
		*p = getchar();
		break;
	case '[':
		if ((*p) == 0) {
			int loopc = 0;
			for(;;)
			{
				c = getc(input);
				if (loopc == 0 && c == ']') break;
				if (c == ']') loopc--;
				if (c == '[') loopc++;
			}
		}else{
			break;
		}
	case ']':
		if((*p) != 0){
			pos = ftell(input)-1;
			int loopc = 0;
			for(;;)
			{
				fseek(input, --pos, SEEK_SET);
				c = getc(input);
				if (loopc == 0 && c == '[') break;
				if (c == ']') loopc++;
				if (c == '[') loopc--;
			}
		}else{
			break;
		}
	}
}

/**
 * @brief Executes the bf program 
 * 
 * 
 */
void execute_program(FILE *input, enum EXEC_MODE mode)
{
	char command;
	char console_in;
	enum EXEC_MODE exec_mode = mode;
	if(exec_mode == STEPS){
		print_program(0, input);
	}
	else{
		system(CLEAR);
	}

	while((command = getc(input)) != EOF ){
		if( is_command(command) ){
			if(exec_mode == STEPS){
	    		printf("Press enter to execute next instruction [%c]: ", command);
	    		scanf("%c", &console_in);
			}
			execute_command(command, input);
			if(exec_mode == STEPS)
			    print_program(command, input);
		}		
	}

	if(exec_mode == CONSOLE_ONLY)
		print_console();
	else if(exec_mode == CONSOLE_MEMORY)
		print_program(0, input);	
}

char* help(){
	return "Simple Brainfuck Interpreter\nThis is an interpreter "
	"for programs written in brainfuck.\nIf you "
	"want to learn more about this language please visit "
	"http://es.wikipedia.org/wiki/Brainfuck.\n\n "
	"Synopsis\n\tsbfi OPTION NAME_OF_FILE\n"
	"Description:\n\tRun a Brainfuck program according to OPTION:\n "
	"\t-s Executes step by step, outputs console and memory\n"
	"\t-a Executes all at once, outputs console and memory\n"
	"\t-c Executes all once, outputs console only\n\n";
}
/**
 * @brief Reads the arguments and then executes the program
 * @param argc 
 * @param argv 
 * @returns 
 * 
 * 
 */
int main(int argc, char **argv) {
	char command, exec_option;
	FILE *input;
	const char *arg[] = {"--help", "-h"};
	if (strcmp(argv[1], arg[0])==0 || strcmp(argv[1], arg[1])==0){
		printf("%s", help());
		return -1;
	}else{
		exec_option = *++argv[1];
		
		input = fopen(argv[2],"r");
		if (input == NULL) {
			fprintf(stderr, "Unable to open \"%s\"\n", argv[2]);
		return -1;
		}	
		
	}
	
	//setting the console
	last_c = &bf_console[0];
	curr_c = &bf_console[0];
	
	//setting the available memory
	last_p = &bf_memory[0];
	p      = &bf_memory[0];
	
	execute_program(input, exec_option);
	return 0;
}
