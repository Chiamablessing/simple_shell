#include "shell.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @boolian: type of swap (0 for swap, non-zero for reverse swap)
 * Return: swapped string
 */
char *swap_char(char *input, int boolian)
{
	int j;

	if (boolian == 0)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == '|')
			{
				if (input[j + 1] != '|')
					input[j] = 16;
				else
					j++;
			}

			if (input[j] == '&')
			{
				if (input[j + 1] != '&')
					input[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input[j]; j++)
		{
			input[j] = (input[j] == 16 ? '|' : input[j]);
			input[j] = (input[j] == 12 ? '&' : input[j]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * gTo_next - go to the next command line stored
 *
 * @list_s: String containing separator list
 * @list_l: command line list
 * @datast: data structure
 * Return: no return
 */
void gTo_next(sep_list **list_s, line_list **list_l, data_shell *datast)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datast->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split1_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datast: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split1_commands(data_shell *datast, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datast->input = list_l->line;
		datast->args = split_line(datast->input);
		loop = exec_line(datast);
		free(datast->args);

		if (loop == 0)
			break;

		gTo_next(&list_s, &list_l, datast);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - function that tokenizes the input string
 *
 * @input: input string.
 * Return: splitted string.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
			free(tokens);
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	free(token);
	return (tokens);
}
