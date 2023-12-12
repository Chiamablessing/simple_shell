#include "shell.h"

/**
 * check_env - function that checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @datas: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *datas)
{
	int row, chr, i, lval;
	char **_envr;

	_envr = datas->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (i = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, i, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[i] == _envr[row][chr])
				i++;
			else
				break;
		}
	}

	for (i = 0; in[i]; i++)
	{
		if (in[i] == ' ' || in[i] == '\t' || in[i] == ';' || in[i] == '\n')
			break;
	}

	add_rvar_node(h, i, NULL, 0);
}

/**
 * check_var - function that check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @datas: data structure
 * Return: no return
 */
int check_var(r_var **h, char *in, char *st, data_shell *datas)
{
	int j, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(datas->pid);

	for (j = 0; in[j]; j++)
	{
		if (in[j] == '$')
		{
			if (in[j + 1] == '?')
				add_rvar_node(h, 2, st, lst), j++;
			else if (in[j + 1] == '$')
				add_rvar_node(h, 2, datas->pid, lpd), j++;
			else if (in[j + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + j, datas);
		}
	}

	return (j);
}

/**
 * replaced_input - functon that replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_vars - functions that calls to replace string into vars
 *
 * @input: input string
 * @datast: data structure
 * Return: replaced string
 */
char *rep_vars(char *input, data_shell *datast)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = my_itoa(datast->status);
	head = NULL;

	olen = check_var(&head, input, status, datast);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
