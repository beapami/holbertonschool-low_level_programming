#include "dog.h"
#include <stdlib.h>

/**
 * _strlen - Returns string length
 * @s: String to evaluate
 * Return: Length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s && s[i])
		i++;
	return (i);
}

/**
 * _strcpy - Copies a string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * new_dog - Creates a new dog
 * @name: Dog's name
 * @age: Dog's age
 * @owner: Dog's owner
 * Return: Pointer to new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *d;

	if (!name || !owner)
		return (NULL);

	d = malloc(sizeof(dog_t));
	if (!d)
		return (NULL);

	d->name = malloc(_strlen(name) + 1);
	d->owner = malloc(_strlen(owner) + 1);
	if (!d->name || !d->owner)
	{
		free(d->name);
		free(d->owner);
		free(d);
		return (NULL);
	}

	_strcpy(d->name, name);
	d->age = age;
	_strcpy(d->owner, owner);

	return (d);
}
