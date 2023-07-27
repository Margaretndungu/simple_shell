#include "main.h"
/**
 * my_getline - reads characters from STDIN
 *
 * Return: allocated string
 */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int index;
	int c;

	while ((c = getchar()) != '\n')
	{
		if (c == EOF)
		{
			return (NULL);
		}
		buffer[index++] = c;

		if (index == BUFFER_SIZE -1)
		{
			buffer[index] = '\0';
			index = 0;
		}
	}
	buffer[index] = '\0';

	index = 0;

	return strdup(buffer);
}
