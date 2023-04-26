#ifndef _MAIN_H_
#define _MAIN_H_
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define SEED -1
#define READ 0
#define WRITE 1
#define FREE 2

/**
 * struct built_in - Struct built_in
 *
 * @name: name of associated command
 * @f: function to be called
 */
typedef struct built_in
{
	char *name;
	int (*f)(char **args);
} bi_t;

/**
 * getInput - get string input from the user
 *
 * @mode: 2 - Free memory
 *
 * Return: pointer to string input
 */
char *getInput(int mode);

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 * @delims: string characters to tokenize by
 *		defaults to ' ' and '\t' if NULL
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s, char *delims);

/**
 * executeCommand - run a command in the shell
 *
 * @args: pointer to a vector of C strings,
 *		ending with a NULL pointer
 *
 * Return: void
 */
void executeCommand(char **args);

/**
 * accessErrorCode - get or set error code
 *
 * @code: error code to set
 * @mode:	1 - set code
 * Return: error code set or requested
 */
int accessErrorCode(int code, int mode);

/**
 * printError - print out an error that occured based on a code
 * @cmd: command that caused the error
 * @shell: name of shell application
 *
 * Return: void
 */
void printError(char *cmd, char *shell);

/**
 * repl - describe a transaction of:
 *		1. Taking input from the user
 *		2. Executing said input
 *		3. Printing any output
 *
 * @argc: number of arguments passed to main
 * @argv: arguments passed to main
 *
 * Return: void
 */
void repl(int argc, char **argv);

/**
 * _getenv - get the value of an environment variable
 *
 * @name: environment variable to search for
 *
 * Return:	pointer to environment variable string
 *		NULL if not found
 */
char *_getenv(char *name);

/**
 * _setenv - set the value of an environment variable
 *
 * @name: environment variable to set
 * @value: value to set it to
 *
 * Return:	pointer to environment variable string
 *		NULL on unset
 */
char *_setenv(char *name, char *value);

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return:	< 0 if s1 < s2
 *		> 0 if s1 > s2
 *		0 otherwise
 */
int _strcmp(char *s1, char *s2);

/**
 * _strlen - get the string length
 *
 * @s: string to calculate length of
 *
 * Return: integer
 */
int _strlen(char *s);

/**
 * _strdup - copies a string to new heap location
 *
 * @s: string to copy
 *
 * Return: pointer to new string copy
 */
char *_strdup(char *s);

/**
 * _strjoin - joins two strings, with an optional joining string
 *		returning a new pointer to string
 * @a: first string
 * @b: second string
 * @j: optional jointer string
 *
 * Return: pointer to new string
 */
char *_strjoin(char *a, char *b, char *j);

/**
 * _environ - get environment variables from anywhere, statically
 *
 * @env:	environment variables to store, NULL to reuse stored
 * @mode:	0 - default, ovewrites environ to env if exists
 *		1 - free environ then quit (ignores env)
 *
 * Return:	pointer to environment variable strings
 *		NULL if environment not previously given
 */
char **_environ(char **env, int mode);

/**
 * _strcontains - check whether a string contains a substring
 *
 * @s: string to check
 * @sub: substring to look for
 *
 * Return:	index of first occurrence substring is found
 *		-1 if not found
 */
int _strcontains(char *s, char *sub);

/**
 * _strtok_r - returns pointers to string as tokens based on delimiters
 *		a new token is given on subsquent calls, NULL if none found
 *
 * @s: string to tokenize
 * @delim: characters to split the string by
 * @start: keep track of last position in string
 *
 * Return: pointer to string tokens or NULL if none
 */
char *_strtok_r(char *s, char *delim, char **start);

/**
 * _realloc - reallocates memory for an array of data
 *
 * @arr: array of data to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: char pointer;
 */
char *_realloc(char *arr, int old_size, int new_size);

/**
 * _reallocp - reallocates memory for an array of pointers
 *
 * @arr: array of pointers to reallocate memory for
 * @old_size: old size of the array, to copy items over
 * @new_size: new size of the reallocated array
 *
 * Return: char pointer to pointers
 */
char **_reallocp(char **arr, int old_size, int new_size);

/**
 * getCmdPath - check whether a command exist in another path
 *		and return that path
 *
 * @cmd: command to check in the PATH variable
 *
 * Return:	new path if exists
 *		NULL if path does not exist
 */
char *getCmdPath(char *cmd);

/**
 * filterComment - find an indicator in the command and end the string there
 *
 * @s: command to check for comment indicator
 * @indicator: indicator that signifies a comment e.g. "#"
 *
 * Return: void
 */
void filterComment(char *s, char *indicator);

/**
 * stripCharacters - strip from the beginning and end of string
 *
 * @str: string to remove edge characters
 * @chars: characters to strip
 *
 * Return: pointer to new string
 */
char *stripCharacters(char *str, char *chars);

/**
 * _strsubstitute - replace occurrences of a subtring with a string
 *
 * @str: original string
 * @sub: substring to replace
 * @rep: strint to replace substring by
 *
 * Return:	pointer to new string
 *		NULL on failure
 */
char *_strsubstitute(char *str, char *sub, char *rep);

/**
 * _freeTokenized - free pointer to strings data
 *
 * @arr: array to be freed
 *
 * Return:	 1 - success
 *		-1 - failure
 */
int _freeTokenized(char **arr);

/**
 * _atoi - convert a string to an integer
 * @s: string to convert to integer
 *
 * Return: int
 */
int _atoi(char *s);

/**
 * _itoa - convert an integer to a string
 *
 * @n:integer to convert to a string
 *
 * Return:	pointer to string
 *		NULL on failure
 */
char *_itoa(int n);

/**
 * endSignal - clean the static environment variable
 *
 * @sig: signal received
 *
 * Return: void
 */
void endSignal(int sig);

/**
 * bi_exit - exit the shell
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_exit(char **args);

/**
 * bi_cd - change current working directory
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_cd(char **args);

/**
 * bi_env - print the environment variables
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_env(char **args);

/**
 * bi_setenv - insert/update an environment variable
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_setenv(char **args);

/**
 * bi_unsetenv - remove an environment variable
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_unsetenv(char **args);

int (*getBuiltin(char *cmd))(char **args);

/**
 * execBuiltin - execute a command if it is a builtin
 *
 * @args: command typed to shell
 *
 * Return: void
 */
void execBuiltin(char **args);

/**
 * _aliases - get/set aliases from anywhere, statically
 *
 * @args:	alias to store, NULL to reuse stored
 * @mode:	-1 - initial seed (no free)
 *		0 - returns aliases (ignores args)
 *		1 - sets aliases, then returns it
 *		2 - free aliases then quit (ignores env)
 *
 * Return:	pointer to aliases strings
 *		NULL if args not previously given
 */
char **_aliases(char **args, int mode);

/*
 * bi_alias - insert/update an alias
 *
 * @args: arguments to function
 *
 * Return:	 1 - success
 *		-1 - fail
 */
int bi_alias(char **args);

/**
 * _getalias - get the value of an alias
 *
 * @name: alias to search for
 *
 * Return:	pointer to alias string
 *		NULL if not found
 */
char *_getalias(char *name);

/**
 * tokenizeCommand - separate a command based on logical operators
 *
 * @s: command string to tokenize
 *
 * Return: pointer to two lists of commands and logical operators
 */
char ***tokenizeCommand(char *s);

/**
 * cleanMemory - free in use memory, such as statically allocated memory
 *
 * Return: void
 */
void cleanMemory(void);

/**
 * _accesscmds - return commands and logical operators tokenized
 *
 * @args:	two lists of commands and logical operators
 * @mode:	0 - returns cmds (ignores args)
 *		1 - sets cmds, then returns it
 *		2 - free cmds then quit (ignores env)
 *
 * Return: pointer to lists of command and logical operators
 */
char ***_accesscmds(char ***args, int mode);

/**
 * parseVariables - go through tokens and replace environment variables
 *
 * @tokens: list of strings to replace if possible
 *
 * Return: void
 */
void parseVariables(char **tokens);

/**
 * continueChain - determine whether to continue executing
 *			a chained command
 * @op: logical operator or ';'
 * @errorCode: last error code
 *
 * Return:	1 for true
 *		0 for false
 */
int continueChain(char *op, int errorCode);

/**
 * execScript - execute commands in a file line by line
 *
 * @argc: number of arguments passed to main
 * @argv: arguments passed to main
 *
 * Return: void
 */
void execScript(int argc, char **argv);

/**
 * _readfile - open a file and read in the contents to memory
 *
 * @filename: name of file to read content from
 *
 * Return: pointer to strings list
 */
char **_readfile(char *filename);

#endif /* _MAIN_H_ */
