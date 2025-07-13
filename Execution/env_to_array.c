/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:31 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/13 20:43:03 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*make_env_entry(t_env *tmp)
{
	char	*str;
	char	*entry;

	str = ft_strjoin(tmp->key, "=");
	if (!str)
		return (NULL);
	entry = ft_strjoin(str, tmp->value);
	free(str);
	return (entry);
}

char	**env_list_to_array(t_env *env)
{
	int		count;
	char	**envp;
	int		i;

	count = env_count(env);
	envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = make_env_entry(env);
		if (!envp[i])
			return (NULL);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
