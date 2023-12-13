#include "shell.h"

/**
* check_delimiter - a function that checks if a character matches any character
* @ch: character to check
* @string: a string of delimiters
* Return: 1 on success, 0 on failure
*/

unsigned int check_delimiter(char ch, const char *string)
{
unsigned int i;
for (i = 0; string[i] != '\0'; i++)
{
if (ch == string[i])
return (1);
}
return (0);
}

/**
* _strtok - function that extracts tokens of a string
* @string: string
* @delimiter: the delimiter
* Return: pointer to the next token or NULL
*/

char *_strtok(char *string, const char *delimiter)
{
static char *tokens;
static char *new_token;
unsigned int i;
if (string != NULL)
new_token = string;
tokens = new_token;
if (tokens == NULL)
return (NULL);
for (i = 0; tokens[i] != '\0'; i++)
{
if (check_delimiter(tokens[i], delimiter) == 0)
break;
}
if (new_token[i] == '\0' || new_token[i] == '#')
{
new_token = NULL;
return (NULL);
}
tokens = new_token + i;
new_token = tokens;
for (i = 0; new_token[i] != '\0'; i++)
{
if (check_delimiter(new_token[i], delimiter) == 1)
break;
}
if (new_token[i] == '\0')
new_token = NULL;
else
{
new_token[i] = '\0';
new_token = new_token + i + 1;
if (*new_token == '\0')
new_token = NULL;
}
return (tokens);
}
