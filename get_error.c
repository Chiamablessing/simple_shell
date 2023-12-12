#include "shell.h"

/**
 * get_error - function that calls the error.
 * according to the builtin, parse or permission
 * @datast: data structure that contains the arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datast, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datast);
		break;
	case 126:
		/* error = error_path_126(datast); */
		break;
	case 127:
		error = error_not_found(datast);
		break;
	case 2:
		if (_strcmp("exit", datast->args[0]) == 0)
			error = error_exit_shell(datast);
		else if (_strcmp("cd", datast->args[0]) == 0)
			error = error_get_cd(datast);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datast->status = eval;
	return (eval);
}
