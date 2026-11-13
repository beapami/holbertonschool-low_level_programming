#include "dog.h"
#include <stdlib.h>

/**
 * free_dog - Frees a dog structure and its allocated members
 * @d: Pointer to the dog_t struct to free
 *
 * Return: Nothing.
 */
void free_dog(dog_t *d)
{
	if (d != NULL)
	{
		free(d->name);
		free(d->owner);
		free(d);
	}
}
