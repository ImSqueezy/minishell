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


void	free_minishell(t_pdata *ptr, char *read_line)
{
	if (read_line)
		free(read_line);
	pdata_lstclear(ptr, true, del); // freed heredoc
	env_lstclear(&ptr->env, del);
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

int	minishell_executer(t_gdata *gdata, t_pdata *pdata)
{
	char	*read;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		pdata->heredoc_strs = NULL;
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n"), free_minishell(pdata, read), gdata->exit);
		if (is_spaces(read))
		{
			free(read);
			continue ;
		}
		if (parser(read, pdata, gdata))
			executer(gdata);
		tcmd_lstclear(&gdata->cmds);
		pdata_lstclear(pdata, true,del); // freed heredoc
		free(gdata->saved_pwd);
		free(read);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pdata	pdata;
	t_gdata	gdata;
	int		ret;

	pdata.token_saved_address = NULL;
	(1) && (pdata.env = NULL, pdata.token = NULL);
	(1) && (gdata.exit = 0, rl_catch_signals = 0);
	get_env(&pdata.env, env);
	if (!pdata.env || !isatty(1))
		return (env_lstclear(&pdata.env, del), 1);
	signal(SIGQUIT, SIG_IGN);
	ret = minishell_executer(&gdata, &pdata);
	return (ret);
}
