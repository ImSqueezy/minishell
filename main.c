/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/03 21:16:19 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint;

void free_heredoc_strs(char **strs)
{
	int i;

	i = 0;
	if (!strs)
		return;
	while(strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_minishell(t_pdata *ptr)
{
	token_lstclear(&ptr->token, del);
	env_lstclear(&ptr->env, del);
	free_heredoc_strs(ptr->heredoc_strs);
	ptr->heredoc_strs = NULL;
}


void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int is_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return 0;
		i++;
	}
	return 1;
}


int	main(int ac, char **av, char **env)
{
	t_pdata	pdata;
	t_gdata	gdata;
	char	*read;

	rl_catch_signals = 0;
	(1) && (pdata.env = NULL, pdata.token = NULL, gdata.exit = 0);
	get_env(&pdata.env, env);
	if (!pdata.env || !isatty(1))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		pdata.heredoc_strs = NULL;
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n"), free_minishell(&pdata), gdata.exit);
		if (is_spaces(read))
		{
			free(read);
			continue ;
		}
		if (parser(read, &pdata, &gdata))
			executer(&gdata);
		free(read);
		free_heredoc_strs(pdata.heredoc_strs);
	}
	return (0);
}
