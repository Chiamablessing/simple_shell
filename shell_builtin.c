#include "shell.h"
/**
 * shell_builtin - function of builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*shell_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", shell_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		 { "cd", cd_dr },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int j;

	for (j = 0; builtin[j].name; j++)
	{
		if (_strcmp(builtin[j].name, cmd) == 0)
			break;
	}

	return (builtin[j].p);
}
