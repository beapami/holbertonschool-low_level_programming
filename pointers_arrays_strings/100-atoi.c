#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to convert.
 *
 * Return: The integer found in the string, or 0 if there is no number.
 */
int _atoi(char *s)
{
	int i;
	int sign;
	int n;
	int found;

	sign = 1;
	n = 0;
	found = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			found = 1;
			n = n * 10 - (s[i] - '0');
		}
		else if (found)
			break;
		else if (s[i] == '-')
			sign = -sign;
	}

	if (sign == 1)
		n = -n;

	return (n);
}
