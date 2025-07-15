/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:50:12 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 18:30:03 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_cmd *cmd)
{
	if (!*cmd->cmd)
		return (0);
	if (!ft_strcmp(*cmd->cmd, "echo") || !ft_strcmp(*cmd->cmd, "export")
		|| !ft_strcmp(*cmd->cmd, "pwd") || !ft_strcmp(*cmd->cmd, "unset")
		|| !ft_strcmp(*cmd->cmd, "cd") || !ft_strcmp(*cmd->cmd, "env")
		|| !ft_strcmp(*cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *current, t_gdata *ptr)
{
	if (!ft_strcmp(current->cmd[0], "echo"))
		return (echo(current->cmd));
	if (!ft_strcmp(current->cmd[0], "export"))
		return (export(ptr, current, 0, 0));
	if (!ft_strcmp(current->cmd[0], "env"))
		return (env(ptr->env));
	if (!ft_strcmp(current->cmd[0], "unset"))
		return (unset(ptr, current->cmd));
	if (!ft_strcmp(current->cmd[0], "cd"))
		return (cd(ptr, current->cmd));
	if (!ft_strcmp(current->cmd[0], "pwd"))
		return (pwd(ptr));
	if (!ft_strcmp(current->cmd[0], "exit"))
		return (exit_builtin(current->cmd, ptr->exit));
	return (0);
}

char	*get_env_v(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
