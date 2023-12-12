#include "shell.h"

/**
 * revs_string - reverses a string.
 * @str: input string.
 * Return: no return.
 */
void revs_string(char *str)
{
	int count = 0, a, b;
	char *s = NULL, temp;

	/* return while loop */
	str = s;

	for (a = 0; a < (count - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			temp = *(str + b);
			*(str + b) = *(str + (b - 1));
			*(str + (b - 1)) = temp;
		}
	}
}
