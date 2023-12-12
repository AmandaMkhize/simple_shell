#include "shell.h"

/*
* _getline - Reads input from the standard input by the user.
* Return: The input stored in a buffer.
*/

char *_getline()
{
int i, rd, buffsize = BUFSIZE;
char c = 0, *buffer, *buf;
buffer = malloc(buffsize);
if (buffer == NULL)
{
free(buffer);
return (NULL);
}
for (i = 0; c != EOF && c != '\n'; i++)
{
fflush(stdin);
rd = read(STDIN_FILENO, &c, 1);
if (rd == 0)
{
free(buffer);
exit(EXIT_SUCCESS);
}
buffer[i] = c;
if (buffer[0] == '\n')
return (enter(buffer));
if (i >= buffsize)
{
buffer = realloc(buffer, (buffsize + 2));
if (buffer == NULL)
{
free(buffer);
return (NULL);
}
}
}
buffer[i] = '\0';
buf = space(buffer);
free(buffer);
hashtag_handler(buf);
return (buf);
}
/*
* enter - Handles the newline character input.
* @string: The string to be handled.
* Return: returns An empty string.
*/
char *enter(char *string)
{
free(string);
return ("\0");
}
/*
* w_space - removes whitespaces.
* @str: The input to be modified.
* Return: The modified string.
*/
char *w_space(char *str)
{
int i, j = 0;
char *buff;
buff = malloc(sizeof(char) * (_strlen(str) + 1));
if (buff == NULL)
{
free(buff);
return (NULL);
}
for (i = 0; str[i] == ' '; i++)
;
for (; str[i + 1] != '\0'; i++)
{
buff[j] = str[i];
j++;
}
buff[j] = '\0';
if (buff[0] == '\0' || buff[0] == '#')
{
free(buff);
return ("\0");
}
return (buff);
}
/**
* hashtag_handler - removes everything after '#'
* @buff: the input buffer
* Return: returns nothing
*/
void hashtag_handler(char *buff)
{
int i;
for (i = 0; buff[i] != '\0'; i++)
{
if (buff[i] == '#' && buff[i - 1] == ' ' && buff[i + 1] == ' ')
{
buff[i] = '\0';
}
}
}
