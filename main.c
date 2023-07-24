#include "main.h"
/**
 * main - entry point
 * Return:Always 0 (success)
 */
int main(void)
{
	char *line;

	while (1)
	{
		prompt_user_file1();
		fflush(stdout);

		line = readCommand_file4();

		if (line == NULL)
		{
			break;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		executeCommand(line);

		free(line);
	}
	return (0);
}
/**
 * executeExternalCommand - function that calls executable files
 * @line:line to be executed
 * Return: 0 on success and -1 on failure
 */
int executeExternalCommand(char *line)
{
	char *command_path;
	int status;
	pid_t pid;
	char *args[MAX_ARGS];

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (pid == 0)
		{
			tokenizeInput_file3(line, args);
			command_path = findCommand_file3(args);

			if (command_path != NULL)
			{
				execve(command_path, args, NULL);
				perror("execve");
				free(command_path);
			}
			else
			{
				char error_message[] = "Command not found: ";

				write(STDERR_FILENO, error_message, strlen(error_message));
				write(STDERR_FILENO, args[0], strlen(args[0]));
				write(STDERR_FILENO, "\n", 1);
			}
			free(line);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
		return (status);
}
/**
 * executeCommand - function that executes all files
 * @line: line to be executed
 * Return: 0 on success
 */
int executeCommand(char *line)
{
	int status __attribute__((unused));
	char *command_path __attribute__((unused));

	if(strcmp(line, "env") == 0)
	{
		printEnvironment_file5();
	}
	else
	{
		if (strstr(line, "/bin/") != NULL)
		{
		status = executeExternalCommand(line);
		}
		else
		{
			char *args[MAX_ARGS];
			tokenizeInput_file3(line, args);
			command_path = findCommand_file3(args);
			status = executeExternalCommand(line);
		}
	}
	return (0);
}
