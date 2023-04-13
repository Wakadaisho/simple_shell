#include "main.h"

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 * Return: void
 */
void repl(void)
{
	char *cmd = NULL;
	char **tokens =  NULL;

	/*Get user input*/
	cmd = getInput();

	/*Tokenize input*/
	tokens = tokenize(cmd);

	/*Execute command*/
	executeCommand(tokens);

	free(tokens);
	free(cmd);
}

