#include "main.h"

/**
  * prompt_user - prompt the user to imput a command
  *
  * Return: Nothing
  */

void prompt_user(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

/**
  * read_line - reads the user imput command
  *
  * Return: the number of characters read, including delimiter character
  * -1 on failure
  */

char *read_line()
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read = getline(&line, &bufsize, stdin);

	if (read == -1)
	{
		if (line)
			free(line);
		write(STDOUT_FILENO. "\n", 1);
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';
	return (line);
}

/**
  * execute_command - execute a command using execve function
  * @command: command to be executed
  *
  * Return: Nothing
  * -1 on failure
  */

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
  * main - entry point
  *
  * Return: Always 0 (success)
  */

int main(void)
{
	char *line;

	while (1)
	{
		prompt_user();
		line = read_line();

		if (line == NULL)
			break;

		execute_command(line);
		free(line);
	}
	return (0);
}
