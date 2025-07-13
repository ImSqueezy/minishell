/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:12 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/13 20:45:51 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_command(t_gdata *data)
{
	int	pid;

	if (!handle_redirections(data->cmds->reds))
	{
		data->exit = 1;
		return ;
	}
	if (is_built_in(data->cmds))
		data->exit = execute_builtin(data->cmds, data);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			command_in_child(data->cmds, data);
		}
		else
			data->exit = get_exit_status(pid);
	}
}
