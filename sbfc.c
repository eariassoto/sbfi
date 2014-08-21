/**
 * Simple Brainfuck Compiler.
 * This program interprets programs written in the esoteric language
 * brainfuck. 
 * Between implementation options are executing the program step by step
 * or all the program at once.
 * 
 * @author Emmanuel Arias
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>

/**
 * @brief type for the memory of the program 
 * 
 * 
 */
typedef char cell;

///Usually, the rules for compiling bf programs sets a maximum memory
static cell bf_memory[30000];
static cell *p, *last_p;

static char bf_console[30000];
static char *curr_c, *last_c;

/**
 * @brief Prints the output of the program.
 * 
 * 
 */
void print_console(){
	char *c = &bf_console[0];
	printf("Console:\n");
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
	printf("Memory Address\tValue\n");
	cell *curr_p = &bf_memory[0];
	while(curr_p <= last_p){
		printf("%p\t%d", curr_p, *curr_p);
		if(curr_p == p)
			printf("\t* pointer is here");
		printf("\n");
		++curr_p;
	}
	printf("\n");
}

/**
 * @brief Prints the command executed by the step by step mode.
 * @param c Command executed
 * 
 * 
 */
void print_command(char c){
	printf("Command executed: %c\n", c);
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
	printf("Instructions: ");
	while( (c = getc(input)) != EOF ){
		printf("%c",c);
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
int isCommand(char c){
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
	system("clear");
	print_instructions(input);
	printf("\n");
	print_console();
	printf("\n");
	if( isCommand(command) ){
		print_command(command);
		printf("\n");
	}
	print_memory();
	printf("\n");
}

/**
 * @brief 
 * @param by_steps 
 * @param command 
 * @param input 
 * 
 * 
 */
void execute_command(char by_steps, char command, FILE *input)
{
	char c, console_in;
	long pos;
	
	if(by_steps){
	    printf("Press enter to execute next instruction (%c): ", command);
	    scanf("%c", &console_in);
	}
	
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
		*curr_c = *p; //don't need to check limits.
		++curr_c;
		++last_c;
		break;
	case ',':
		*p = getchar();
		break;
	case '[':
		pos = ftell(input);
		if ((*p) == 0) {
			int loopc = 0;
			for(;;)
			{
				c = getc(input);
				if (loopc == 0 && c == ']') break;
				if (c == ']') loopc--;
				if (c == '[') loopc++;
			}
		} else while((*p) != 0) {
			fseek(input, pos, SEEK_SET);
			c = getc(input);
			while( c!=']' && c!=EOF) {
				execute_command(by_steps, c,input);
				c = getc(input);
			}
		}
	}
	if(by_steps)
	    print_program(command, input);
}

/**
 * @brief Executes the program by steps.
 * @param input Stream with the bf program.
 * 
 * 
 */
void execute_by_steps(FILE *input){
	char command;
	
	print_program('e', input);
	while((command = getc(input)) != EOF ){
		execute_command(1, command, input);
	}
}

/**
 * @brief Executes the program all at once.
 * @param input Stream with the bf program.
 * 
 * 
 */
void execute_at_once(FILE *input){
	char command;
	while((command = getc(input)) != EOF ){
		execute_command(0, command, input);
	}
	print_program('e', input);
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
	///for now I'll just assume the input program only by files.
	if (argc < 3){
		//print help TODO make help
		return -1;
	}else{
		//TODO need to validate arguments
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
	
	switch(exec_option){
		case 's':
			execute_by_steps(input);
		break;
		case 'a':
			execute_at_once(input);
		break;
	}
	return 0;
}
