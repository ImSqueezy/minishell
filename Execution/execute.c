/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:10:15 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:27:43 by asadkaou         ###   ########.fr       */
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
		handle_cmd_not_found(cmd->cmd[0]);
	envp = env_list_to_array(data->env);
	if (!envp)
		handle_env_failure(path);
	if (access(path, X_OK) == -1)
		handle_permission_denied(cmd->cmd[0]);
	execve(path, cmd->cmd, envp);
	perror("execve");
	exit(1);
}

int	get_exit_status(int pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_putstr_fd("\n", 1);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit", 1);
		return (128 + sig);
	}
	return (1);
}

void	reset_fds(t_gdata *data)
{
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	close(data->saved_stdin);
	close(data->saved_stdout);
}
