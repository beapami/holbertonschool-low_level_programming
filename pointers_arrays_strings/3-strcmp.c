#include "main.h"

/**
 * _strcmp - Compares two strings, exactly like strcmp.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: A value less than, equal to, or greater than 0, depending on
 * whether s1 is found to be less than, equal to, or greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}
