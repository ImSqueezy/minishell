/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:09:55 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:09:57 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*try_paths(char **paths, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		if (!full)
			break ;
		full = set_newstr(full, cmd, ft_strlen(cmd));
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

char	*find_command_in_path(char *cmd, t_env *env)
{
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_execution_split(get_env_v(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	return (try_paths(paths, cmd));
}

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
