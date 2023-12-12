#include "shell.h"

/**
 * *_strcpy - a function that creates a copy
 *	of a string
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */

char *_strcpy(char *dest, char *src)
{
	char *ptr_dest = dest;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (ptr_dest);
}
/**
 * _strcat - concatenates two strings
 * @dest: char pointer of the copied str dest
 * @src: const char pointer of the source str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - function compare two strings
 * @s1: parameter of type str compared
 * @s2: parameter of type str compared
 * Return: Always 0.
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strspn - calculate the length of a prefixed substring.
 * @str:Pointer to the null-terminated string to be analyzed.
 * @accept: accepted bytes containing the character.
 * Return: the number of accepted bytes.
 */
int _strspn(char *str, char *accept)
{
	int i, j, boolian;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		boolian = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(str + i) == *(accept + j))
			{
				boolian = 0;
				break;
			}
		}
		if (boolian == 1)
			break;
	}
	return (i);
}
/**
 * _strchr - locates a character in a string,
 * @str: pointer to the null-terminated string.
 * @c: character to search for in the string.
 * Return: the pointer to the first occurrence of the character c
 *         otherwise NULL
 */
char *_strchr(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}
