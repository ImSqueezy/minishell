/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:25 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/13 20:42:22 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_in_child(t_cmd *cmd, t_gdata *data)
{
	char	*path;
	char	**envp;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		exit(0);
	if (ft_strchr(cmd->cmd[0], '/'))
		path = ft_strdup(cmd->cmd[0]);
	else
		path = find_command_in_path(cmd->cmd[0], data->env);
	if (!path)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	envp = env_list_to_array(data->env);
	if (!envp)
	{
		ft_putendl_fd("Failed to prepare environment", 2);
		free(path);
		exit(1);
	}
	execve(path, cmd->cmd, envp);
	perror("execve");
	exit(1);
}

int	get_exit_status(int pid)
{
	int	status;
	int	signal;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit", 1);
		return (128 + signal);
	}
	return (1);
}
