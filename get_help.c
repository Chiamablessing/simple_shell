#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datast: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_shell *datast)
{

	if (datast->args[1] == 0)
		cham_help_general();
	else if (_strcmp(datast->args[1], "setenv") == 0)
		cham_help_setenv();
	else if (_strcmp(datast->args[1], "env") == 0)
		cham_help_env();
	else if (_strcmp(datast->args[1], "unsetenv") == 0)
		cham_help_unsetenv();
	else if (_strcmp(datast->args[1], "help") == 0)
		cham_help();
	else if (_strcmp(datast->args[1], "exit") == 0)
		cham_help_exit();
	else if (_strcmp(datast->args[1], "cd") == 0)
		cham_help_cd();
	else if (_strcmp(datast->args[1], "alias") == 0)
		cham_help_alias();
	else
		write(STDERR_FILENO, datast->args[0],
		      _strlen(datast->args[0]));

	datast->status = 0;
	return (1);
}
