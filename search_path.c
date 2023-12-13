#include "shell.h"

/**
* path_cmd - Search in $PATH for an executable command.
* @cmd: Parsed input command
* Return: 0 on success, 1 on failure
*/

int path_cmd(char **cmd)
{
char *searchPath, *pathValue, *cmdPath;
struct stat buf;
searchPath = _getenv("PATH");
pathValue = _strtok(searchPath, ":");
while (pathValue != NULL)
{
cmdPath = build(*cmd, pathValue);
if (stat(cmdPath, &buf) == 0)
{
*cmd = _strdup(cmdPath);
free(cmdPath);
free(searchPath);
return (0);
}
free(cmdPath);
pathValue = _strtok(NULL, ":");
}
free(searchPath);
free(pathValue);
return (1);
}
/**
* build - Constructs the full path of an executable command
* @token: The executable command
* @value: The directory containing the command
* Return: The parsed full path of the command, or NULL if construction fails
*/
char *build(char *token, char *pathValue)
{
char *cmd;
size_t len;
len = _strlen(pathValue) + _strlen(token) + 2;
cmd = malloc(sizeof(char) * len);
if (cmd == NULL)
{
free(cmd);
return (NULL);
}
memset(cmd, 0, len);
cmd = _strcat(cmd, pathValue);
cmd = _strcat(cmd, "/");
cmd = _strcat(cmd, token);
return (cmd);
}
/**
* _getenv - Gets the value of environment variable by name
* @name: Environment variable name
* Return: The value of the environment variable or NULL if failed
*/
char *_getenv(char *name)
{
size_t name_len, value_len;
char *value;
int i, j, k;
name_len = _strlen(name);
for (i = 0 ; environ[i]; i++)
{
if (_strncmp(name, environ[i], name_len) == 0)
{
value_len = _strlen(environ[i]) - name_len;
value = malloc(sizeof(char) * value_len);
if (!value)
{
free(value);
perror("unable to alloc");
return (NULL);
}
j = 0;
for (k = name_len + 1; environ[i][k]; k++, j++)
{
value[j] = environ[i][k];
}
value[j] = '\0';
return (value);
}
}
return (NULL);
}
