/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:15 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/22 18:02:52 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parsing.h"

char	*get_key(char *p)
{
	char	*key;
	int		i;

	i = 0;
	while (p[i] && p[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (p[i] && p[i] != '=')
	{
		key[i] = p[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static void	env_add_back(t_env **head, t_env *new)
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
	if (p)
		p++;
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
	t_env	*new;

	*ptr = NULL;
	i = -1;
	while (env[++i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->key = get_key(env[i]);
		new->value = get_value(env[i]);
		new->next = NULL;
		env_add_back(ptr, new);
	}
}
