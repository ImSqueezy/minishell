/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:49:15 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 07:13:59 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	expanded_key(t_env *env, char *str)
{
	t_env	*curr;
	char	*key;
	char	*tmp;
	int		i;

	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (0);
	i = 1;
	while (tmp[i])
		i++;
	key = ft_strdup(&tmp[1]);
	if (key[0] == '\0')
		return (0);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (free(key), 0);
		curr = curr->next;
	}
	return (free(key), 1);
}

t_red	*red_addnew(t_env *env, t_token *lst)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	new->fname = ft_strdup(lst->word);
	new->type = define_ftype(lst->prev->type);
	new->ambiguous = 0;
	if ((!lst->word || !ft_strcmp(lst->word, "")
			|| expanded_key(env, lst->word)) && lst->type != delimiter)
		new->ambiguous = 1;
	new->heredoc_string = NULL;
	new->next = NULL;
	return (new);
}

t_red	*reds_init(t_token *lst, t_pdata *data)
{
	t_token	*curr;
	t_red	*head;
	t_red	*new;

	(1) && (head = NULL, curr = lst);
	while (curr)
	{
		if (curr->type == file || curr->type == delimiter)
		{
			new = red_addnew(data->env, curr);
			if (new->type == heredoc)
			{
				new->heredoc_string = ft_strdup(
						data->heredoc_strs[data->heredoc_count]);
				data->heredoc_count++;
			}
			red_addback(&head, new);
		}
		if (curr->next && curr->next->type == PIPE)
			break ;
		curr = curr->next;
	}
	return (head);
}

t_cmd	*cmd_addnew(t_token *lst, t_pdata *data)
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
	new->reds = reds_init(lst, data);
	return (new);
}
