#include "shell.h"

/**
 * int_data - function that initiallize data structure
 *
 * @datast: data structure
 * @av: argument vector
 * Return: no return
 */
void int_data(data_shell *datast, char **av)
{
	unsigned int j;

	datast->av = av;
	datast->input = NULL;
	datast->args = NULL;
	datast->status = 0;
	datast->counter = 1;

	for (j = 0; environ[j]; j++)
		;

	datast->_environ = malloc(sizeof(char *) * (j + 1));

	for (j = 0; environ[j]; j++)
	{
		datast->_environ[j] = _strdup(environ[j]);
	}

	datast->_environ[j] = NULL;
	datast->pid = my_itoa(getpid());
}


/**
 * free_data - function that frees data structure
 *
 * @datast: data structure
 * Return: no return
 */
void free_data(data_shell *datast)
{
	unsigned int j;

	for (j = 0; datast->_environ[j]; j++)
	{
		free(datast->_environ[j]);
	}

	free(datast->_environ);
	free(datast->pid);
}


/**
 * main - Entry point of function
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datast;
	(void) ac;

	signal(SIGINT, sigint_handler);
	int_data(&datast, av);
	shell_lp(&datast);
	free_data(&datast);
	if (datast.status < 0)
		return (255);
	return (datast.status);
}


