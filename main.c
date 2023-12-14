#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 256

void prompt_and_read_input(char **user_input);
void handle_command(char **cmd, char **user_input,
		char **argv, int *count, int *stat);

/**
* alt_main - Entry point to the program
* @argc: the argument count
* @argv: the argument vector
* Return: Returns the condition
*/
int alt_main(__attribute__((unused)) int argc, char **argv)
{
char *user_input, **cmd, **commands;
int count = 0, i, condition = 1, stat = 0;
signal(SIGINT, signal_to_handle);

while (condition)
{
count++;
prompt_and_read_input(&user_input);
if (user_input[0] == '\0')
continue;

history(user_input);
commands = separator(user_input);

for (i = 0; commands[i] != NULL; i++)
{
cmd = parse_cmd(commands[i]);
handle_command(cmd, &user_input, argv, &count, &stat);
}

free(user_input);
free(commands);
wait(&stat);
}

return (stat);
}

/**
* prompt_and_read_input - Prompt the user and read input
* @user_input: Pointer to store user input
*/
void prompt_and_read_input(char **user_input)
{
if (isatty(STDIN_FILENO))
prompt();

*user_input = _getline();
}

/**
* handle_command - Handle the command
* @cmd: Parsed command
* @user_input: User input
* @argv: Argument vector
* @count: Pointer to count
* @stat: Pointer to status
*/
void handle_command(char **cmd, char **user_input,
		char **argv, int *count, int *stat)
{
if (_strcmp(cmd[0], "exit") == 0)
{
free(*cmd);
exit_bul(cmd, *user_input, argv, *count, *stat);
}
else if (check_builtin(cmd) == 0)
{
*stat = handle_builtin(cmd, *stat);
free(*cmd);
}
else
*stat = check_cmd(cmd, *user_input, *count, argv);

free(*cmd);
}

/**
* read_command - Read a command from the user
* @buffer: The buffer to store the command
* @prompt: The prompt to display to the user
* Return: Returns 1 if successful, 0 otherwise
*/
int read_command(char *buffer, const char *prompt)
{
printf("%s", prompt);

return (fgets(buffer, BUF_SIZE, stdin) != NULL);
}

/**
* handle_eof - Handle end-of-file condition.
* @buffer: The buffer to check for end-of-file
* Return: Returns 1 if end-of-file is reached, 0 otherwise
*/
int handle_eof(__attribute__((unused)) char *buffer)
{
if (feof(stdin))
{
printf("\n");
return (1);
}
return (0);
}

/**
* process_command - Process a command
* @buffer: The command to process
* Return: Returns 0 if successful, 1 otherwise
*/
int process_command(char *buffer)
{
pid_t pid;

if (strlen(buffer) == 0)
{
return (0);
}

pid = fork();

if (strchr(buffer, ' ') != NULL)
{
printf("Error: Command should be a single word\n");
return (0);
}
if (pid == -1)
{
perror("fork failed");
return (0);
}
if (pid == 0)
{
char *args[2];
args[0] = buffer;
args[1] = NULL;

if (execve(buffer, args, environ) == -1)
{
printf("%s: No such file or directory\n", buffer);
exit(1);
}
}
else
{
int status;
waitpid(pid, &status, 0);

if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
{
printf("Error executing command\n");
}
}
return (0);
}
/**
* main - Entry point to the shell program
* Return: Exit status
*/
int main(void)
{
char buffer[BUF_SIZE];
const char prompt[] = "#cisfun$ ";

while (1)
{
if (!read_command(buffer, prompt))
{
break;
}
if (handle_eof(buffer))
{
break;
}
process_command(buffer);
}
return (0);
}

