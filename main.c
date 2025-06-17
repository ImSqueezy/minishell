<<<<<<< HEAD

#include "execution.h" // contient la struct t_cmd + prototype execute_command

// void f()
// {
//     system("lsof -c execute");
// }
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/26 19:01:00 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/parsing.h"
>>>>>>> master

int	parser(char *input, t_pdata *pdata)
{
	t_gdata	*gdata;
	char	*newinput;

	add_history(input);
	lexer(input, pdata, gdata);
	expansions_search(pdata);
	token_lstclear(&pdata->token, del);
	return (1);
}

void	free_minishell(t_pdata *ptr)
{
	token_lstclear(&ptr->token, del);
	env_lstclear(&ptr->env, del);
}

int	main(int ac, char **av, char **env)
{
<<<<<<< HEAD
    t_cmd cmd;
    // atexit (f);
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    // Remplir la structure
    cmd.cmd = &argv[1];           // ex: ./execute ls -l → cmd.cmd = ["ls", "-l", NULL]
    cmd.first = argv[1];          // le nom de la commande (ex: "ls")
    cmd.fd_in = STDIN_FILENO;
    cmd.fd_out = STDOUT_FILENO;
    cmd.env = NULL;               // adapte selon ton projet

    execute_command(&cmd, envp);

    return 0;
=======
	t_pdata	pdata;
	char	*read;

	pdata.env = NULL;
	pdata.token = NULL;
	get_env(&pdata.env, env);
	while (1)
	{
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n"), free_minishell(&pdata), 0);
		parser(read, &pdata);
	}
	return (0);
>>>>>>> master
}
