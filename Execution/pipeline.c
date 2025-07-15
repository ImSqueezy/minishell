/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:10:26 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:10:27 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_command(t_gdata *data)
{
	int	pid;

	if (!handle_redirections(data->cmds->reds))
		return ((void)(data->exit = 1));
	if (is_built_in(data->cmds))
		return ((void)(data->exit = execute_builtin(data->cmds, data)));
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

void	after_fork(t_gdata *data, t_cmd *cur, int *save_read, int *fds)
{
	if (cur != data->cmds)
	{
		dup2(*save_read, 0);
		close(*save_read);
	}
	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
	if (!handle_redirections(cur->reds))
		exit(1);
	if (is_built_in(cur))
		exit(execute_builtin(cur, data));
	command_in_child(cur, data);
}

int	execute_command(t_cmd *cur, t_gdata *data, int *save_read)
{
	int	pid;
	int	fds[2];

	if (cur->next)
		pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		after_fork(data, cur, save_read, fds);
	}
	else
	{
		if (cur != data->cmds)
			close(*save_read);
		*save_read = fds[0];
		close(fds[1]);
	}
	return (pid);
}
