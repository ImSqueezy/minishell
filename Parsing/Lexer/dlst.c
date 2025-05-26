/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:51:49 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/26 18:50:29 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

void	token_lstdelone(t_token **head, t_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (*head == lst)
		*head = lst->next;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	del(lst->word);
	free(lst);
}

void	token_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*next;
	t_token	**head;

	head = lst;
	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		token_lstdelone(head, *lst, del);
		*lst = next;
	}
	*lst = NULL;
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}

t_token	*token_addnew(char *word, int type, int quoting, int var)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = word;
	new_node->type = type;
	new_node->quoting = quoting;
	new_node->var = var;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	token_insert_after(t_token *current, t_token *new_node)
{
	if (!current || !new_node)
		return ;
	new_node->prev = current;
	new_node->next = current->next;
	if (current->next)
		current->next->prev = new_node;
	current->next = new_node;
}
