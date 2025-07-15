/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:09:35 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:35:49 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	handle_cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	handle_env_failure(char *path)
{
	free(path);
	ft_putendl_fd("Failed to prepare env", 2);
	exit(1);
}

void	handle_permission_denied(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	exit(126);
}
