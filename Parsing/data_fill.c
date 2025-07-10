/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:49:15 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/03 12:49:20 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red_addback(t_red **lst, t_red *new)
{
	t_red	*ptr;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr && ptr->next)
		ptr = ptr->next;
	(*ptr).next = new;
}

void	cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr && ptr->next)
		ptr = ptr->next;
	(*ptr).next = new;
}

t_red	*red_addnew(t_token *lst)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	while (lst)
	{
		if (lst->type == file || lst->type == delimiter)
		{
			new->fname = ft_strdup(lst->word);
			new->type = define_ftype(lst->prev->type);
			new->expand = 0;
			if (lst->type == delimiter && lst->quoting == 1)
				new->expand = 1;
			new->ambiguous = 0;
			if (!lst->word || ft_strchr(new->fname, ' '))
				new->ambiguous = 1;
			new->next = NULL;
			break ;
		}
		lst = lst->next;
	}
	return (new);
}

t_red	*reds_init(t_token *lst)
{
	t_token	*curr;
	t_red	*head;

	head = NULL;
	curr = lst;
	while (curr)
	{
		if (curr->type == file || curr->type == delimiter)
			red_addback(&head, red_addnew(curr));
		if (curr->next && curr->next->type == PIPE)
			break ;
		curr = curr->next;
	}
	return (head);
}

t_cmd	*cmd_addnew(t_token *lst)
{
	t_token	*curr;
	t_cmd	*new;
	int		i;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (lst->prev && lst->prev->type != PIPE)
		lst = lst->prev;
	new->cmd = malloc(
			(cmds_reds_counter(lst, CMDS_COUNT) + 1) * sizeof(char *));
	if (!new->cmd)
		return (NULL);
	(1) && (i = 0, curr = lst);
	while (curr)
	{
		if (curr->type == command)
			new->cmd[i++] = ft_strdup(curr->word);
		if (curr->next && curr->next->type == PIPE)
			break ;
		curr = curr->next;
	}
	(1) && (new->cmd[i] = NULL, new->next = NULL);
	new->reds = reds_init(lst);
	return (new);
}
