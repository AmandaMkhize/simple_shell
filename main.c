<<<<<<< HEAD
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
=======
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 256

int read_command(char *buffer, const char *prompt)
{
	printf("%s", prompt);

	return (fgets(buffer, BUF_SIZE, stdin) != NULL);

}
int handle_eof(char *buffer)
{
	if (feof(stdin))
	{
		printf("\n");
		return (1);
	}
	return (0);
}
int process_command(char *buffer)
{
	if (strlen(buffer) == 0)
	{
		return (0);
	}
	if (strchr(buffer, ' ') != NULL)
	{
		printf("Error: Command should be a single word\n");
		return (0);

}
	pid_t pid = fork();

	if (pid == -1)
	{
	perror("fork failed");

	return (0);
	}
	if (pid == 0)
{
	if (execve(buffer, (char *const [])
				{buffer, NULL}, environ) == -1)
	{
		printf("%s: No such file or directory\n", buffer);
		exit(1);
	}
}	else
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

>>>>>>> c519e0bb08a68c79ec46bc6413c13e3838b86971
