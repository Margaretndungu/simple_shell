#include "main.h"
/**
  * split_arguments_file2 - splits a line
  * @line: pointer to be splitted
  * @args: pointer to the arguments
  *
  * Return: pointer to next token or NULL if there are no more
  */

void split_arguments_file2(char *line, char **args)
{
	int i = 0;
	char *token;

	token = strtok(line, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
  * execute_command_file2 - executes a command
  * @line: pointer to the line to be executed
  *
  * Return: Nothing or -1 on error
  */

void execute_command_file2(char *line)
{
	pid_t pid = fork();
	int exec_result;

	line[strcspn(line, "\n")] = '\0';

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[64];

		split_arguments_file2(line, args);

		exec_result = execve(args[0], args, NULL);

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
