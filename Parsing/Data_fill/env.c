/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:15 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 07:13:41 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_addnew(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

char	*get_key(char *p)
{
	char	*key;
	int		i;

	i = 0;
	while (p[i] && p[i] != '=' && p[i] != ' ')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (p[i] && p[i] != '=' && p[i] != ' ')
	{
		key[i] = p[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	env_addback(t_env **head, t_env *new)
{
	t_env	*ptr;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

char	*get_value(char *p)
{
	char	*value;
	int		i;

	while (*p && *p != '=')
		p++;
	if (*p)
		p++;
	else
		return (NULL);
	i = 0;
	while (p[i])
		i++;
	value = malloc(sizeof(char) * i + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (p[i])
	{
		value[i] = p[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

void	get_env(t_env **ptr, char **env)
{
	int		i;
	char	*key;
	char	*value;

	*ptr = NULL;
	i = -1;
	while (env[++i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		env_addback(ptr, env_addnew(key, value));
		free(key);
		free(value);
	}
}
