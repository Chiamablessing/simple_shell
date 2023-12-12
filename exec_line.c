#include "shell.h"

/**
 * exec_line - function that finds builtins and commands
 *
 * @datast: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *datast)
{
	/* int (*builtin)(data_shell *datast); */

	if (datast->args[0] == NULL)
		return (1);
	return (cmd_exec(datast));
}
