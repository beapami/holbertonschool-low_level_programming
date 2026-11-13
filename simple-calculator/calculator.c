#include <stdio.h>

/**
 * main - Entry point for the simple calculator
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int choice;
	float a, b;

	printf("Simple Calculator\n");
	do {
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\n");
		printf("Choice: ");

		if (scanf("%d", &choice) != 1)
			break;

		if (choice >= 1 && choice <= 4)
		{
			printf("A: ");
			if (scanf("%f", &a) != 1)
				break;
			printf("B: ");
			if (scanf("%f", &b) != 1)
				break;

			if (choice == 1)
				printf("Result: %.0f\n", a + b);
			else if (choice == 2)
				printf("Result: %.0f\n", a - b);
			else if (choice == 3)
				printf("Result: %.0f\n", a * b);
			else if (choice == 4)
			{
				if (b == 0)
					printf("Error: division by zero\n");
				else
					printf("Result: %.1f\n", a / b);
			}
		}
		else if (choice == 0)
		{
			printf("Bye!\n");
		}
		else
		{
			printf("Invalid choice\n");
		}
	} while (choice != 0);

	return (0);
}
