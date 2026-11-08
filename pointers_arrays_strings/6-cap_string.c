#include "main.h"

/**
 * is_separator - Checks if a character is a word separator.
 * @c: The character to check.
 *
 * Return: 1 if c is a separator, 0 otherwise.
 */
int is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ';' ||
	    c == '.' || c == '!' || c == '?' || c == '"' || c == '(' ||
	    c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

/**
 * cap_string - Capitalizes all words of a string.
 * @str: The string to modify.
 *
 * Return: A pointer to the modified string.
 */
char *cap_string(char *str)
{
	int i;
	int new_word;

	i = 0;
	new_word = 1;
	while (str[i] != '\0')
	{
		if (new_word && str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 'a' + 'A';
		new_word = is_separator(str[i]);
		i++;
	}

	return (str);
}
