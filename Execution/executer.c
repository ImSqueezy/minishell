/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:50:12 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/04 10:10:00 by aouaalla         ###   ########.fr       */
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
	if (!ft_strcmp(ptr->cmds->cmd, "echo"))
		return (echo(ptr->cmds->cmd));
	if (!ft_strcmp(ptr->cmds->cmd, ""))
		return (export(ptr));
	return (0);
}

void	execute(t_gdata *ptr)
{
	if (is_built_in(ptr->cmds))
		ptr->exit = execute_builtin(ptr->cmds->cmd);
}

void	executer(t_gdata	*data)
{
	if (data->cmds && !data->cmds->next)
		execute(data);
	return ;
}
