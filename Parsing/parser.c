/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:16:28 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/01 18:16:4 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define REDS_COUNT 1
#define CMDS_COUNT 0

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

static int	cmds_reds_counter(t_token *cmd, int count_flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd)
	{
		if (cmd->type == command)
			i++;
		else if (cmd->type == red_in || cmd->type == red_out
			|| cmd->type == append || cmd->type == heredoc)
			j++;
		if (cmd->next && cmd->next->type == PIPE)
			break ;
		cmd = cmd->next;
	}
	if (count_flag == REDS_COUNT)
		return (j);
	else if (count_flag == CMDS_COUNT)
		return (i);
	return (1337);
}

static int	define_ftype(int type)
{
	if (type == red_out)
		return (red_out);
	else if (type == red_in)
		return (red_in);
	else if (type == append)
		return (append);
	else
		return (heredoc);
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
			new->expand = 1;
			if (!ft_strcmp(lst->word, ""))
				new->ambiguous = 0;
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

void	cmds_init(t_pdata *pdata, t_gdata *gdata)
{
	t_token	*curr;
	t_token	*next;

	gdata->env = pdata->env;
	gdata->cmds = NULL;
	curr = pdata->token;
	while (curr)
	{
		next = curr->next;
		if (!next || next->type == PIPE)
			cmd_addback(&gdata->cmds, cmd_addnew(curr));
		curr = next;
	}
}

/* quick debugger for filled data
	t_cmd *curr1 = head;
	t_red	*curr2;
	int		i;
	int		j;
	while (curr1)
	{
		i = 0;
		printf("commands:\n");
		while (curr1->cmd[i])
			printf("> [%s] \n", curr1->cmd[i++]);
		printf("reds:\n");
		curr2 = curr1->reds;
		j = 0;
		while (curr2)
		{
			printf("- - red number %d - -\n", j++);
			print_tokens(curr2->fname, curr2->type);
			printf("> expand: %d\n", curr2->expand);
			printf("> ambiguous: %d\n", curr2->ambiguous);
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}
*/

int	parser(char *input, t_pdata *pdata, t_gdata *gdata)
{
	t_token	*t_cpy;
	char	*newinput;

	add_history(input);
	if (!lexer(pdata, input))
		return (token_lstclear(&pdata->token, del), gdata->exit = 258, 0);
	expansions_search(pdata, gdata);
	t_cpy = pdata->token;
	while (t_cpy)
	{
		if (t_cpy->var != 3)
			t_cpy->word = quote_removal(t_cpy, t_cpy->word);
		t_cpy = t_cpy->next;
	}
	cmds_init(pdata, gdata);
	return (token_lstclear(&pdata->token, del), 1);
}
