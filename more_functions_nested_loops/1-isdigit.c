#include "main.h"

/**
 * _isupper - Vérifie si un caractère est en majuscule.
 * @c: Le caractère à vérifier (passé sous forme d'entier).
 *
 * Return: 1 si c est une majuscule, 0 sinon.
 */
int  _isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
