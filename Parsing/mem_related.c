/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:48:18 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/30 19:45:32 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	env_lstclear(t_env **head, void (*del)(void *))
{
	t_env	*next;

	if (!head || !del)
		return ;
	while (*head)
	{
		next = (*head)->next;
		env_lstdelone(*head, del);
		*head = next;
	}
	*head = NULL;
}

void	env_lstdelone(t_env *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->key);
	del(node->value);
	free(node);
}
