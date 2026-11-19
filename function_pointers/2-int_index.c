#include "function_pointers.h"
#include <stdlib.h>

/**
 * int_index - Searches for an integer using a comparison function
 * @array: Pointer to the integer array
 * @size: Number of elements in the array
 * @cmp: Pointer to the function used to compare values
 *
 * Return: Index of the first element for which cmp does not return 0,
 *         or -1 if no match or size <= 0
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array != NULL && cmp != NULL && size > 0)
	{
		for (i = 0; i < size; i++)
		{
			if (cmp(array[i]) != 0)
				return (i);
		}
	}
	return (-1);
}
