/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 22:01:55 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_minishell_exit_status(int status)
{
	if (g_sigint)
		return (1);
	return (status);
}

int	minishell_executer(t_gdata *gdata, t_pdata *pdata)
{
	char	*read;

	while (1)
	{
		pdata->heredoc_strs = NULL;
		signal(SIGINT, sigint_handler);
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n")
				, free_minishell(pdata, read), free(gdata->saved_pwd)
				, get_minishell_exit_status(gdata->exit));
		if (g_sigint)
			(1) && (gdata->exit = 1, g_sigint = 0);
		if (is_spaces(read))
		{
			free(read);
			continue ;
		}
		add_history(read);
		if (parser(read, pdata, gdata))
			executer(gdata);
		data_clear(gdata, pdata, read);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pdata	pdata;
	t_gdata	gdata;
	int		ret;

	(void)ac;
	(void)av;
	gdata.pdata = &pdata;
	pdata.env = NULL;
	pdata.token = NULL;
	gdata.saved_pwd = NULL;
	gdata.cmds = NULL;
	gdata.exit = 0;
	g_sigint = 0;
	rl_catch_signals = 0;
	get_env(&pdata.env, env);
	if (!isatty(1) || !isatty(0))
		return (env_lstclear(&pdata.env, del), 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ret = minishell_executer(&gdata, &pdata);
	return (ret);
}
