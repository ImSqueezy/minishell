/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:41:10 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/13 21:53:50 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_access(char **paths, char *cmd, int i, char **full_path)
{
	*full_path = ft_strjoin(paths[i], "/");
	if (!*full_path)
		return (0);
	*full_path = set_newstr(*full_path, cmd, ft_strlen(cmd));
	if (!*full_path)
		return (0);
	if (access(*full_path, X_OK) == 0)
		return (1);
	free(*full_path);
	return (0);
}

char	*find_command_in_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_execution_split(get_env_v(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (check_access(paths, cmd, i, &full_path))
		{
			free_string_array(paths);
			return (full_path);
		}
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

/*
static char	*try_path(char *dir, char *cmd)
{
	char	*path;
	char	*full;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	full = set_newstr(path, cmd, ft_strlen(cmd));
	free(path);
	return (full);
}

char	*find_command_in_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*full;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_execution_split(get_env_v(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full = try_path(paths[i], cmd);
		if (!full)
			break ;
		if (access(full, X_OK) == 0)
			return (free_string_array(paths), full);
		free(full);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}
*/

char	*generate_path(void)
{
	int		i;
	char	*num;
	char	*str;

	i = 0;
	while (1)
	{
		num = ft_itoa(i++);
		if (!num)
			return (NULL);
		str = ft_strjoin("/tmp/.here_doc", num);
		free(num);
		if (!str)
			return (NULL);
		if (access(str, F_OK) == -1)
			return (str);
		free(str);
	}
}
