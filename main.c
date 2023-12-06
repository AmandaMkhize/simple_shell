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

