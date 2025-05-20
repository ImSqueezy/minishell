#include "Includes/parsing.h"

int	parser(char *input, t_pdata *pdata)
{
	t_gdata	*gdata;
	char	*newinput;

	add_history(input);
	lexer(input, pdata, gdata); // processes input filles pdata if a parse error didn't occur
	return (1);
}


int main(int ac , char **av, char **env)
{
	t_pdata pdata;
	char	*read;

	get_env(pdata.env, env);
	while (1)
	{
		read = readline("$");
		if (!read)
			return (0);
		parser(read, &pdata);
	}
	return (0);
}
