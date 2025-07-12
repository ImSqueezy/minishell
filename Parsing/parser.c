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

static void	data_init(t_pdata *pdata, t_gdata *gdata)
{
	t_env	*ecurr;
	t_token	*tcurr;
	t_token	*next;

	(1) && (gdata->env = pdata->env, ecurr = gdata->env
		, gdata->cmds = NULL, gdata->saved_pwd = NULL);
	while (ecurr)
	{
		if (!ft_strcmp(ecurr->key, "PWD"))
		{
			gdata->saved_pwd = ft_strdup(ecurr->value);
			break ;
		}
		ecurr = ecurr->next;
	}
	tcurr = pdata->token;
	while (tcurr)
	{
		next = tcurr->next;
		if (!next || next->type == PIPE)
			cmd_addback(&gdata->cmds, cmd_addnew(tcurr, pdata));
		tcurr = next;
	}
}

void	quote_suppression(t_token *head)
{
	t_token	*t_cpy;

	t_cpy = head;
	while (t_cpy)
	{
		if (t_cpy->var != 3)
			t_cpy->word = quote_removal(t_cpy, t_cpy->word);
		t_cpy = t_cpy->next;
	}
}

int	parser(char *input, t_pdata *pdata, t_gdata *gdata)
{
	char	*newinput;
	int		save_in;

	add_history(input);
	if (!lexer(pdata, input))
		return (pdata_lstclear(pdata, false, del), gdata->exit = 258, 0);
	save_in = dup(STDIN_FILENO);
	pdata->heredoc_count = 0;
	pdata->heredoc_strs = get_heredoc_strings(pdata->token, pdata->env);
	if (g_sigint)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
		g_sigint = 0;
		return (pdata_lstclear(pdata, true, del), 0);
	}
	expansions_search(pdata, gdata);
	quote_suppression(pdata->token);
	data_init(pdata, gdata);
	return (pdata_lstclear(pdata, true, del), 1);
}

/* quick token debuger
	t_token *curr;
	curr = data->token;
	while (curr)
	{
		print_tokens(curr->word, curr->type);
		printf("- - - - -\n");
		curr = curr->next;
	}
*/

/* quick data
	t_cmd	*curr1;
	t_red	*curr2;
	int		i;
	curr1 = gdata->cmds;
	while (curr1)
	{
		i = 0;
		printf("command:\n");
		while (curr1->cmd[i])
		{
			printf("%s\n", curr1->cmd[i]);
			i++;
		}
		printf("redirect:\n");
		curr2 = curr1->reds;
		while (curr2)
		{
			printf("file name: %s am: %d\n", curr2->fname, curr2->ambiguous);
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}
*/