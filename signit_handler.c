#include "shell.h"

/**
 * sigint_handler - function that Handles the "crtl + c" command in prompt
 * @sig: Signal handler
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 5);
}
