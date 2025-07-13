/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:54 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/13 20:44:40 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	after_fork(t_gdata *data, t_cmd *cur, int *save_read, int *fds)
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

void	reset_fds(t_gdata *data)
{
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	close(data->saved_stdin);
	close(data->saved_stdout);
}

static void	exec_pipeline(t_gdata *data, t_cmd *cur, int save_read)
{
	int	pid;

	while (cur)
	{
		pid = execute_command(cur, data, &save_read);
		cur = cur->next;
	}
	reset_fds(data);
	data->exit = get_exit_status(pid);
	while (wait(NULL) != -1)
		;
}

void	executer(t_gdata *data)
{
	t_cmd	*current;
	int		save_read;

	current = data->cmds;
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	save_read = -1;
	if (!current)
	{
		data->exit = 0;
		return ;
	}
	if (!current->next)
	{
		single_command(data);
		reset_fds(data);
		return ;
	}
	exec_pipeline(data, current, save_read);
}
