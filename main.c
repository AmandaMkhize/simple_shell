#include "shell.h"

/**
* main - Entry point to the program
* @argc: the argument count
* @argv: the argument vector
* Return: Returns the condition
*/
int main(__attribute__((unused)) int argc, char **argv)
{
char *user_input, **cmd, **commands;
int count = 0, i, condition = 1, stat = 0;

if (argv[1] != NULL)
read_file(argv[1], argv);
signal(SIGINT, signal_to_handle);
while (condition)
{
count++;
if (isatty(STDIN_FILENO))
prompt();
user_input = _getline();
if (user_input[0] == '\0')
continue;
history(user_input);
commands = separator(user_input);
for (i = 0; commands[i] != NULL; i++)
{
cmd = parse_cmd(commands[i]);
if (_strcmp(cmd[0], "exit") == 0)
{
free(commands);
exit_bul(cmd, user_input, argv, count, stat);
}
else if (check_builtin(cmd) == 0)
{
stat = handle_builtin(cmd, stat);
free(cmd);
continue;
}
else
stat = check_cmd(cmd, user_input, count, argv);
free(cmd);
}
free(user_input);
free(commands);
wait(&stat);
}
return (stat);
}
