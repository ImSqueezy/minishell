/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 06:06:11 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 06:13:41 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_red(t_red *red)
{
	if (!red)
		return ;
	free(red->fname);
	free(red->heredoc_string);
	free(red);
}

static void	free_reds(t_red *reds)
{
	t_red	*tmp;

	while (reds)
	{
		tmp = reds->next;
		free_red(reds);
		reds = tmp;
	}
}

void	tcmd_lstclear(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		ft_free(lst->cmd);
		free_reds(lst->reds);
		free(lst);
		lst = tmp;
	}
}

/*
	Additional rather than memory related
*/

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
