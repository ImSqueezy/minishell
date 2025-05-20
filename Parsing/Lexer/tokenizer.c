/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blah.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:56:13 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/17 21:56:15 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

static void	token_type(t_token *token)
{
	size_t	len;

	len = ft_strlen(token->word);
	if (len == 1 && token->type != var) // a pipe a redirection or other
	{
		if (!ft_strncmp(token->word, "<", 1)
			|| !ft_strncmp(token->word, ">", 1))
			token->type = redirection;
		else if (!ft_strncmp(token->word, "|", 1))
			token->type = PIPE;
		else
			token->type = word;
	}
	else if (len == 2 && token->type != var) // append, herdoce or other
	{
		if (!ft_strncmp(token->word, ">>", 2)
			|| !ft_strncmp(token->word, "<<", 2))
			token->type = redirection;
		else
			token->type = word;
	}
	else if (len > 2 && token->type != var)
		token->type = word;
}

void	token_definer(char **tokens, t_pdata *data)
{
	int		i;
	t_token	*new_token;

	data->token = NULL;
	i = 0;
	while (tokens[i])
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return ;
		new_token->word = tokens[i];
		new_token->quoting = 0;
		if (ft_strchr(new_token->word, '\''))
			new_token->quoting = 1;
		else if (ft_strchr(new_token->word, '\"'))
			new_token->quoting = 2;
		new_token->next = NULL;
		new_token->prev = NULL;
		token_type(new_token);
		token_add_back(&data->token, new_token);
		i++;
	}
}

static void	ops_definer(t_token *ptr, int *comming_file)
{
    if (ft_strncmp(ptr->word, ">", 1) == 0)
		ptr->type = red_out;
    else if (ft_strncmp(ptr->word, "<", 1) == 0)
        ptr->type = red_in;
    else if (ft_strncmp(ptr->word, ">>", 2) == 0)
        ptr->type = append;
    *comming_file = 1;
    if (ft_strncmp(ptr->word, "<<", 2) == 0)
	{
        ptr->type = heredoc;
		if (ptr->next->type == word)
			ptr->next->type = delimiter;
		*comming_file = 0;
	}
	else if (ft_strncmp(ptr->word, "|", 1) == 0)
	{
		ptr->type = PIPE;
		*comming_file = 0;
	}
}

void	re_definer(t_token *head)
{
	t_token	*curr;
	int		file_onwards;

	curr = head;
	file_onwards = 0;
	while (curr)
	{
		if (curr->type == redirection || curr->type == PIPE)
			ops_definer(curr, &file_onwards);
		else if (file_onwards)
		{
			curr->type = file;
			file_onwards = 0;
		}
		else if ((curr->prev && curr->prev->type == PIPE)
			|| curr->prev == NULL || curr->prev->type == file || curr->prev->type == command)
    		curr->type = command;
		if (ft_strchr(curr->word, '$'))
			curr->type = var;
    	curr = curr->next;
	}
}
