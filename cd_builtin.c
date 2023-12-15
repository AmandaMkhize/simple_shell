#include <stdio.h>
#include "shell.h"

/**
* change_to_directory - Change the current directory to the specified path
* @path: The path to change to
* Return: 0 on success, -1 on failure
*/
static int change_to_directory(const char *path)
{
if (chdir(path) == -1)
{
perror("chdir");
return (-1);
}
return (0);
}

/**
* update_pwd_variables - Update the PWD and OLDPWD environment variables
* @cwd: The current working directory
*/
static void update_pwd_variables(const char *cwd)
{
setenv("OLDPWD", getenv("PWD"), 1);
setenv("PWD", cwd, 1);
}

/**
* change_dir - Changes directory
* @cmd: Parsed command
* @st: Status of the last command executed
* Return: 0 on success, -1 on failure
*/
int change_dir(char **cmd, __attribute__((unused)) int st)
{
char *new_dir;
char cwd[PATH_MAX];

if (cmd[1] == NULL || strcmp(cmd[1], "~") == 0)
{
new_dir = getenv("HOME");
if (new_dir == NULL)
{
perror("cd");
return (-1);
}
}
else if (strcmp(cmd[1], "-") == 0)
{
new_dir = getenv("OLDPWD");
if (new_dir == NULL)
{
perror("cd");
return (-1);
}
printf("%s\n", new_dir);
}
else
{
new_dir = cmd[1];
}
if (change_to_directory(new_dir) == -1)
{
return (-1);
}
if (getcwd(cwd, sizeof(cwd)) == NULL)
{
perror("getcwd");
return (-1);
}
update_pwd_variables(cwd);
return (0);
}

