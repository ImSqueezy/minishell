/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:10:39 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:30:20 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	kill_children(int *pids, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while (wait(NULL) != -1)
		;
}

static int	exec_command_loop_body(t_cmd *cur, t_gdata *data,
		int *save_read, int *i)
{
	data->pids[*i] = execute_command(cur, data, save_read);
	if (data->pids[*i] == -1)
	{
		reset_fds(data);
		kill_children(data->pids, *i + 1);
		free(data->pids);
		return (0);
	}
	(*i)++;
	return (1);
}

static void	exec_multi_commands(t_gdata *data)
{
	t_cmd	*cur;
	int		save_read;
	int		i;

	cur = data->cmds;
	save_read = -1;
	data->pids = malloc((count_cmds(cur) + 1) * sizeof(int));
	if (!data->pids)
		return ;
	i = 0;
	while (cur)
	{
		if (!exec_command_loop_body(cur, data, &save_read, &i))
			return ;
		cur = cur->next;
	}
	data->exit = get_exit_status(data->pids[i - 1]);
	free(data->pids);
	while (wait(NULL) != -1)
		;
}

void	executer(t_gdata *data)
{
	t_cmd	*cur;

	cur = data->cmds;
	if (!cur)
	{
		data->exit = 0;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	if (!cur->next)
	{
		single_command(data);
		reset_fds(data);
		return ;
	}
	exec_multi_commands(data);
	reset_fds(data);
}
