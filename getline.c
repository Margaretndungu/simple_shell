#include "main.h"
/**
 * custon_getline - function that customizes getline
 * Return: Nothing
 */
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index = 0;
	static ssize_t bytes_read = 0;

	char *line = NULL;
	size_t line_length = 0;
	ssize_t i;
	size_t new_line_length;
	char *new_line;

	while (1)
	{
		if ((ssize_t)buffer_index >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				return (NULL);
			}
			buffer_index = 0;
		}
		for(i = buffer_index; i < bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				line = (char *)malloc((line_length + i - buffer_index + 2) * sizeof(char));
				if(!line)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				memcpy(line + line_length, buffer + buffer_index, i - buffer_index + 1);
				line[line_length + i - buffer_index + 1] ='\0';

				buffer_index = i + 1;
				return (line);
			}
		}
		new_line_length = line_length + bytes_read - buffer_index;
		new_line = (char *) realloc(line, (new_line_length + 1) * sizeof(char));
		if (!new_line)
		{
			perror("realloc");
			free(line);
			exit(EXIT_FAILURE);
		}
		line = new_line;
		memcpy(line + line_length, buffer + buffer_index, bytes_read - buffer_index);
		line[new_line_length] = '\0';

		line_length = new_line_length;
		buffer_index = bytes_read;
	}
}
