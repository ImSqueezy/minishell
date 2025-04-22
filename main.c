#include "Includes/parsing.h"

int main(int argc, char **argv, char **envp)
{
	t_env			*envr;
	char			*str;
	struct	termios	term;

	if (argc != 1 || argv[1])
		return (printf("main's args"), 1);
	tcgetattr(0, &term); // set the attributes in term
	// the envr variable must be set
	// the signals must be handled
	// then read from the prompt
	return (0);
}