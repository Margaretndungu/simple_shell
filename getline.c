#include "main.h"
/**
 * prompt_user_file1 - prompt the user
 *
 * Nothing
 */
void prompt_user_file1(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}
/**
 * read_chars_from_buffer - reads characters from the buffer into the line
 * @buffer: buffer containing characters read from input
 * @buffer_length: number of characters read into the buffer
 * @line: line to store the user input
 * @line_index: current index in the line buffer
 * Return: Number of characters read into the line
 */
ssize_t read_chars_from_buffer(const char *buffer,
ssize_t buffer_length, char *line, size_t line_index)
{
	ssize_t buffer_index = 0;
	ssize_t chars_read = 0;

	while (buffer_index < buffer_length)
	{
		if (buffer[buffer_index] == '\n')
		{
			line[line_index] = '\0';
			buffer_index++;
			return (chars_read + 1);
		}
		else
		{
			if (line_index >= READLINE_BUFFER_SIZE - 1)
			{
				write(STDERR_FILENO, "Error: Input exceeds buffer size\n", 32);
				exit(EXIT_FAILURE);
			}
			line[line_index++] = buffer[buffer_index++];
			chars_read++;
		}
	}
	return (chars_read);
}
/**
 * read_line_file1 - reads user input command
 *
 * Return: number of characters read, including the delimiter character
 * -1 on failure
 */
char *read_line_file1(void)
{
	static char buffer[READLINE_BUFFER_SIZE];
	static size_t buffer_index;
	static size_t line_length;

	char chars_read;
	char *line = NULL;
	size_t line_index = 0;

	while (1)
	{
		if (buffer_index >= line_length)
		{
			line_length = read(STDIN_FILENO, buffer, READLINE_BUFFER_SIZE);
			if (line_length <= 0)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			buffer_index = 0;
		}
		if (line == NULL)
		{
			line = (char *)malloc(READLINE_BUFFER_SIZE);
			if (line == NULL)
			{
				write(STDERR_FILENO, "Error: malloc failed\n", 21);
				exit(EXIT_FAILURE);
			}
		}
		chars_read = read_chars_from_buffer(buffer, line_length,
				line, line_index);
		line_index += chars_read;

		if (chars_read > 0)
			return (line);
	}
}
/**
 * execute_command_file1 - executes a command using execve function
 * @command: command to be executed
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
