#include "shell.h"

/**
 * no_comment - function that deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *no_comment(char *in)
{
	int i, max;

	max = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
			max = i;
		}
	}

	if (max != 0)
	{
		in = my_realloc(in, i, max + 1);
		in[max] = '\0';
	}
	return (in);
}

/**
 * shell_lp - function that initiallize Loop of shell
 * @datast: data relevant (av, input, args)
 * Return: no return.
 */
void shell_lp(data_shell *datast)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			if (_strcmp(input, "\n") == 0)
				continue;
			if (input[_strlen(input) - 1] == '\n')
				input[_strlen(input) - 1] = '\0';
			input = no_comment(input);
			if (input == NULL)
				continue;

			if (check_parse_error(datast, input) == 1)
			{
				datast->status = 2;
				free(input);
				continue;
			}
			input = rep_vars(input, datast);
			loop = split1_commands(datast, input);
			datast->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
