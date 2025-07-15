/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:52:22 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 21:52:40 by aouaalla         ###   ########.fr       */
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
