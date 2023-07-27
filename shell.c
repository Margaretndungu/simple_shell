#include "main.h"

/**
  * prompt_user_file1 - prompts a user
  *
  * Return: 0 on success
  */

int prompt_user_file1(void)
{
	if (isatty(STDIN_FILENO))
	{
	write(STDOUT_FILENO, "$ ", 3);
	return (1);
	}
	return (0);
}

/**
  * read_line_file1 - reads user input command
  *
  * Return: number of characters read, including the delimeter character
  * -1 on failure
  */

char *read_line_file1(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read = getline(&line, &bufsize, stdin);

	if (read == -1)
	{
		if (line)
			free(line);
		if (bufsize == 0)
		write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';
	return (line);
}

/**
  * execute_command_file1 - executes a command using execve function
  * @command: command to be executed
  *
  * Return: Nothing
  * -1 on failure
  */

void execute_command_file1(char *command)
{
	pid_t pid = fork();
	int exec_result;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;

		exec_result = execve(command, args, NULL);

		if (exec_result == -1)
		{
			perror("execve");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
