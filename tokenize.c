#include "main.h"

/**
 * _strchr - Find first occurence of a character in a string
 * @str: the string to search
 * @c: The character to find
 *
 * Return: pointer to first occurence of a character in a string
 * NULL if not found
 */

char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}

	return (NULL);
}
/**
 * custom_strtok - Extract tokens from a string
 * @str: the string to tokenize
 * @del: delimeter of tokenization
 *
 * Return: pointer to the next token in the string
 * NULL if no more tokens are found
 */
char *custom_strtok(char *str, const char *del)
{
	static char *current;
	char *token;
	char *next_delimeter;

	if (str)
		current = str;

	if (!current)
		return (NULL);

	token = current;
	next_delimeter = _strchr(current, *del);

	if (next_delimeter)
	{
		*next_delimeter = '\0';
		current = next_delimeter + 1;
	}
	else
	{
		current = NULL;
	}
	return (token);
}
