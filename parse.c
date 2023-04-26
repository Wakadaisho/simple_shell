#include "main.h"

/**
 * getQuotedString - get tokens surrounded by quotes as one string
 *
 * @token: first token with a quote
 * @delims: characters to split the string by
 * @str: keep track of last position in string
 *
 * Return: single string token
 */
char *getQuotedString(char *token, char *delims, char **str)
{
	char *_t = NULL;
	char *q_token = NULL, *q_temp = NULL;
	char l_match = 0, r_match = 0;

	if (token == NULL)
		return (NULL);
	l_match = *token;
	_t = _strdup(token);
	while (_t)
	{
		r_match = _t[_strlen(_t) - 1];
		q_temp = _strjoin(q_token, _t, " ");
		if (q_token)
			free(q_token);
		q_token = q_temp;
		free(_t);
		if (l_match == r_match)
			return (q_token);
		_t = _strdup(_strtok_r(NULL, delims, str));
	}
	if (_t)
		free(_t);
	return (q_token);
}

/**
 * tokenize - split a string into an array of strings
 *		based on certain DELIMS (delimiters)
 * @s: string to split
 * @delims: string characters to tokenize by
 *		defaults to ' ' and '\t' if NULL
 *
 * Return: array of strings, NULL if failed or no s is NULL
 */
char **tokenize(char *s, char *delims)
{
	int n = 10, len = 0;
	char *str, *p, *token = NULL, *q_token = NULL;
	char **tokens;

	if (s == NULL)
		return (NULL);
	tokens = malloc(n * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	p = str = _strdup(s);
	if (p == NULL)
		return (NULL);
	token = _strdup(_strtok_r(str, delims, &str));
	while (token)
	{
		for (; len >= n; n *= 1.5)
			tokens = _reallocp(tokens, n, n * 1.5);
		if (*token == '\'' || *token == '\"')
			q_token = getQuotedString(token, delims, &str);
		if (q_token)
		{
			tokens[len++] = q_token;
			free(token);
			q_token = NULL;
		}
		else
		{
			tokens[len++] = token;
		}
		token = _strdup(_strtok_r(NULL, delims, &str));
	}
	free(p);
	tokens[len] = NULL;
	return (tokens);
}

/**
 * filterComment - find an indicator in the command and end the string there
 *
 * @s: command to check for comment indicator
 * @indicator: indicator that signifies a comment e.g. "#"
 *
 * Return: void
 */
void filterComment(char *s, char *indicator)
{
	int foundComment;

	if (s == NULL)
		return;

	foundComment = _strcontains(s, indicator);

	if (foundComment != -1)
		s[foundComment] = '\0';
}

/**
 * stripCharacters - strip from the beginning and end of string
 *
 * @str: string to remove edge characters
 * @chars: characters to strip
 *
 * Return: pointer to new string
 */
char *stripCharacters(char *str, char *chars)
{
	char *s;
	int i = 0;
	char chrToStr[] = {'\0', '\0'};

	if (str == NULL)
		return (NULL);

	*chrToStr = *(str + i);
	/* ignore chars from front */
	while (_strcontains(chars, chrToStr) != -1)
		*chrToStr = *(str + ++i);

	s = _strdup(str + i);
	if (*s == '\0')
		return (s);

	i = _strlen(s);
	*chrToStr = *(s + i);
	/* null chars from back */
	while (_strcontains(chars, chrToStr) != -1)
	{
		*(s + i) = '\0';
		*chrToStr = *(s + --i);
	}

	return (s);
}

/**
 * tokenizeCommand - separate a command based on logical operators
 *
 * @s: command string to tokenize
 *
 * Return: pointer to two lists of commands and logical operators
 */
char ***tokenizeCommand(char *s)
{
	int ops_len = 0, ops_cap = 2, cmds_len = 0, cmds_cap = 2, i, op;
	char *cmd = NULL, *tmp = NULL;
	char **cmds = malloc(cmds_cap * sizeof(char *));
	char **ops = NULL, **t = tokenize(s, " \r\t");
	char ***ret = malloc(2 * sizeof(char **));

	for (op = 0, i = 0; t[i]; i++, op ^= op)
	{
		op += _strcontains(t[i], "&&") != -1;
		op += _strcontains(t[i], "||") != -1;
		op += _strcontains(t[i], ";") != -1;
		if (op)
		{
			if (ops == NULL)
				ops = malloc(ops_cap * sizeof(char *));
			for (; cmds_len >= cmds_cap - 1; cmds_cap *= 2)
				cmds = _reallocp(cmds, cmds_len, cmds_cap * 2);
			for (; ops_len >= ops_cap - 1; ops_cap *= 2)
				ops = _reallocp(ops, ops_len, ops_cap * 2);
			cmds[cmds_len++] = cmd;
			cmd = NULL;
			cmds[cmds_len] = NULL;
			ops[ops_len++] = _strdup(t[i]);
			ops[ops_len] = NULL;
			continue;
		}
		tmp = _strjoin(cmd, t[i], " ");
		if (cmd)
			free(cmd);
		cmd = tmp;
	}
	for (; cmds_len >= cmds_cap - 1; cmds_cap *= 2)
		cmds = _reallocp(cmds, cmds_len, cmds_cap * 2);
	cmds[cmds_len++] = cmd;
	cmds[cmds_len] = NULL;
	ret[0] = cmds;
	ret[1] = ops;
	_freeTokenized(t);
	return (ret);
}
