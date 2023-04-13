#ifndef _MAIN_H_
#define _MAIN_H_
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * getInput - get string input from the user
 *
 * Return: pointer to string input
 */
char *getInput(void);

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s);

/**
 * executeCommand - run a command in the shell
 *
 * @args: pointer to a vector of C strings,
 *		ending with a NULL pointer
 *
 * Return: execve return value
 */
int executeCommand(char **args);

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 * Return: void
 */
void repl(void);

#endif /* _MAIN_H_ */
