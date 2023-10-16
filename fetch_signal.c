#include "shell.h"

/**
 * signalc - for the crtl-c exit call in shell
 * @signal: handler for signal
 */

void signalc(int signal)
{
	(void)signal; /*suppress the "unused parameter" warning*/
	write(STDOUT_FILENO, "\n$ ", 3);
}
