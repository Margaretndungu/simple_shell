#include "main.h"
/**
 * read_input_line - function that reads user input
 * Return: Nothing
 */
char *read_input_line(void)
{
	char *line = NULL;
	size_t line_size = 0;
	char buffer[BUFFER_SIZE];
	ssize_t chars_read;

	while (1)
	{
		chars_read = read_input_chunk(buffer, BUFFER_SIZE);

		if (chars_read <= 0)
		{
			if (line_size == 0)
				return (NULL);
		}
		line = process_input_data(buffer, chars_read, line, &line_size);
		if (line == NULL)
		{
			return (NULL);
		}
	}
	if (prompt_user_file1() == 0)
		return (NULL);

	execute_command_file1(line);

	return (line);
}
/**
 * read_input_chunk - function that read input
 * @buffer: pointer to buffer character
 * @size:size of the buffer
 * Return: Nothing
 */
ssize_t read_input_chunk(char *buffer, size_t size)
{
	static size_t buffer_pos;
	static ssize_t chars_in_buffer;

	if ((ssize_t)buffer_pos >= chars_in_buffer)
	{
		chars_in_buffer = read(STDIN_FILENO, buffer, size);

		buffer_pos = 0;
	}
	return (chars_in_buffer);
}
/**
 * process_input_data - function that process input
 * @buffer: pointer to a buffer character
 * @chars_read:character to be read
 * @line:pointer to a line character
 * @line_size:function that give line size
 * Return: Nothing
 */
char *process_input_data(const char *buffer,
		ssize_t chars_read, char *line, size_t *line_size)
{
	ssize_t i;
	char current_char;
	char *new_line;

	for (i = 0; i < chars_read; i++)
	{
		current_char = buffer[i];

		if (*line_size == 0 || *line_size % BUFFER_SIZE == 0)
		{
			new_line = realloc(line, *line_size + BUFFER_SIZE);

			if (new_line == NULL)
			{
				free(line);
				return (NULL);
			}
			line =  new_line;
		}
		line[(*line_size)++] = current_char;
		if (current_char == '\n')
		{
			line[*line_size - 1] = '\0';
			return (line);
		}
	}
	return (line);
}
