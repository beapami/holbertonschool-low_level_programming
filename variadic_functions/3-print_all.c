#include "variadic_functions.h"
#include <stdio.h>

/**
 * print_all - Prints anything based on a format string
 * @format: List of types of arguments passed to the function
 *
 * Return: Nothing.
 */
void print_all(const char * const format, ...)
{
	va_list args;
	int i = 0;
	char *sep = "";
	char *str;

	va_start(args, format);

	while (format && format[i])
	{
		switch (format[i])
		{
			case 'c':
				printf("%s%c", sep, va_arg(args, int));
				break;
			case 'i':
				printf("%s%d", sep, va_arg(args, int));
				break;
			case 'f':
				printf("%s%f", sep, (float)va_arg(args, double));
				break;
			case 's':
				str = va_arg(args, char *);
				if (!str)
					str = "(nil)";
				printf("%s%s", sep, str);
				break;
			default:
				i++;
				continue;
		}
		sep = ", ";
		i++;
	}

	va_end(args);
	printf("\n");
}
