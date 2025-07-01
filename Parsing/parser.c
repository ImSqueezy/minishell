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

int	cmds_reds_counter(t_token *cmd, int count_flag)
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

int	define_ftype(int type)
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

static void	cmds_init(t_pdata *pdata, t_gdata *gdata)
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
