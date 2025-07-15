/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:09:26 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:31:42 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_env_str(t_env *tmp)
{
	char	*str;
	char	*res;

	str = ft_strjoin(tmp->key, "=");
	if (!str)
		return (NULL);
	res = ft_strjoin(str, tmp->value);
	free(str);
	return (res);
}

static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = build_env_str(env);
		if (!envp[i])
			return (NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
