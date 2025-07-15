/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:51:49 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 19:30:40 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	del(lst);
}

void	pdata_lstclear(t_pdata *ptr, void (*del)(void *))
{
	t_token	*next;
	t_token	**head;

	head = &ptr->token;
	if (!ptr->token || !del)
		return ;
	while (ptr->token)
	{
		next = (ptr->token)->next;
		token_lstdelone(head, ptr->token, del);
		ptr->token = next;
	}
	ptr->token = NULL;
}

void	token_addback(t_token **lst, t_token *new)
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

t_token	*sub_token_addnew(char *word, t_token *prev)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = word;
	new_node->type = 0;
	new_node->quoting = prev->quoting;
	new_node->var = 0;
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
