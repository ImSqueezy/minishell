/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 06:13:26 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint;

void	free_minishell(t_pdata *ptr, char *read_line)
{
	if (read_line)
		free(read_line);
	pdata_lstclear(ptr, del);
	env_lstclear(&ptr->env, del);
}

void	sigint_handler(int sig)
{
	g_sigint = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	data_clear(t_gdata *gdata, t_pdata *pdata, char *read)
{
	if (gdata->cmds)
	{
		tcmd_lstclear(gdata->cmds);
		gdata->cmds = NULL;
	}
	pdata_lstclear(pdata, del);
	pdata->token = NULL;
	free(read);
}

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

	pdata.env = NULL;
	pdata.token = NULL;
	gdata.saved_pwd = NULL;
	gdata.cmds = NULL;
	gdata.exit = 0;
	g_sigint = 0;
	rl_catch_signals = 0;
	get_env(&pdata.env, env);
	if (!pdata.env || !isatty(1))
		return (env_lstclear(&pdata.env, del), 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ret = minishell_executer(&gdata, &pdata);
	return (ret);
}
