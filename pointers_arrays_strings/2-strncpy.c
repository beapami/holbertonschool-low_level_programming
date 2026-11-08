#include "main.h"

/**
 * _strncpy - Copies a string, exactly like strncpy.
 * @dest: The destination buffer.
 * @src: The string to copy.
 * @n: The number of bytes to write to dest.
 *
 * Return: A pointer to dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
