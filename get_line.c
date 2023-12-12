#include "shell.h"

/**
 * built_line - function assigns the line variable for get_line
 * @lineptr: Buffer that store the input string
 * @buffer: string that is been assigned to the line
 * @n: pointer to the size of line
 * @b: size of buffer
 */
void built_line(char **lineptr, size_t *n, char *buffer, size_t b)
{

	size_t j = 0;

	if (*lineptr == NULL)
	{
		if  (b > BUFSIZE)
			*n = b;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - function that read input from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = my_realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	built_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
