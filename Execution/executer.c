/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:50:12 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/08 12:11:39 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_cmd *cmd)
{
	if (!ft_strcmp(*cmd->cmd, "echo") || !ft_strcmp(*cmd->cmd, "export")
		|| !ft_strcmp(*cmd->cmd, "pwd") || !ft_strcmp(*cmd->cmd, "unset")
		|| !ft_strcmp(*cmd->cmd, "cd") || !ft_strcmp(*cmd->cmd, "env")
		|| !ft_strcmp(*cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_gdata *ptr)
{
	if (!ft_strcmp(*ptr->cmds->cmd, "echo"))
		return (echo(ptr->cmds->cmd));
	if (!ft_strcmp(*ptr->cmds->cmd, "export"))
		return (export(ptr));
	if (!ft_strcmp(*ptr->cmds->cmd, "env") && !ptr->cmds->cmd[1])
		return (env(ptr->env));
	if (!ft_strcmp(*ptr->cmds->cmd, "unset"))
		return (unset(ptr, ptr->cmds->cmd));
	if (!ft_strcmp(*ptr->cmds->cmd, "cd"))
		return (cd(ptr, ptr->cmds->cmd));
	if (!ft_strcmp(*ptr->cmds->cmd, "pwd"))
		return (pwd(ptr));
	return (0);
}

// void	execute(t_gdata *ptr)
// {
// 	if (is_built_in(ptr->cmds))
// 		ptr->exit = execute_builtin(ptr);
// }

void	executer(t_gdata *data)
{
	// if (data->cmds && !data->cmds->next)
	// 	execute(data);
	execute_pipeline(data);
}
