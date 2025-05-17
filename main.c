#include "Includes/parsing.h"

int	parser(char *input, t_pdata *data)
{
	char	*newinput;

	add_history(input);
	lexer(input, data);
	return (1);
}

int main()
{
	t_pdata pdata;
	char	*read;

	while (1)
	{
		read = readline("$");
		if (!read)
			return (0);
		parser(read, &pdata);
	}
	return (0);
}
