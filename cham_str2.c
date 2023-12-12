#include "shell.h"

/**
 *_strlen - function that counts the length of strings
 * @s: Type char pointer
 * Return: returns the string length
 */
size_t _strlen(const char *s)
{
	const char *p = s;

	while (*p)
	{
		p++;
	}
	return (p - s);
}

/**
 * _strdup - duplicates a str in the heap memory.
 * @str: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *str)
{
	char *new_str;
	size_t len;

	len = _strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	_memcpy(new_str, str, len + 1);
	return (new_str);
}

/**
 * cmp_chars - compare chars of strings
 * @str: The string to compare.
 * @delim: The delimiter string for coparison.
 *
 * Return: 1 if every character in str has a match,otherwise 0.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j;

	for (i = 0; str[i]; i++)
	{
		for (j = 0; delim[j] && str[i] != delim[j]; j++)
		{

		}
	}
	if (!delim[j])
		return (0);
	return (1);
}

/**
 *_strtok - a function that split a string by delimeter
 *@str: input sting to be tokenized
 *@delim: delimeter
 *Return: string splitted otherwise NULL
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *tk_end;
	char *tk_start;
	unsigned int i, boolian;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _strlen(str);
		tk_end = &str[i]; /*Store last address*/
	}
	tk_start = splitted;
	if (tk_start == tk_end) /*Reaching the end*/
		return (NULL);

	for (boolian = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != tk_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == tk_start)
					tk_start++;
				break;
			}
		}
		if (boolian == 0 && *splitted) /*Str != Delim*/
			boolian = 1;
	}
	if (boolian == 0) /*Str == Delim*/
		return (NULL);
	return (tk_start);
}

/**
 * _isdigit - check if string passed represent a digit
 *
 * @s: input string
 * Return: 1 if string is a number. otherwise 0.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
