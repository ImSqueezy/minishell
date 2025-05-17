/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:46:45 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/15 21:46:46 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parsing.h"

static int	print_serror(t_token *curr, int op, int state)
{
	if (op == PIPE)
		printf("%s `|'\n", SYNTAX_ERROR);
	else if (op == redirection && state == 1)
		printf("%s `newline'\n", SYNTAX_ERROR);
	else if (op == redirection && state == 0)
		printf("%s `%s'\n", SYNTAX_ERROR, curr->word);
	return (1);
}

/* syntax error memory
	1) checking weither pipe at the beginning or the end
	2) then weither what's before pipe is red or pipe -> works well
	3) also cheching what's after redirection (if not word leave)
	4) at the end, checking weither red is at the beginning or the end
*/

static int	syntax_checker(t_pdata *data)
{
	t_token	*curr;

	curr = data->token;
	while (curr)
	{
		if (curr->type == PIPE && (curr->prev == NULL || curr->next == NULL))
			return (print_serror(curr->next, PIPE, 1), 0);
		else if (curr->type == PIPE
			&& (curr->prev != NULL && curr->prev->type == PIPE))
			return (print_serror(curr->prev, PIPE, 1), 0);
		else if (curr->type == redirection
			&& (curr->next && curr->next->type != word))
			return (print_serror(curr->next, redirection, 0), 0);
		else if ((curr->type == redirection && !curr->prev && !curr->next)
			|| (curr->type == redirection && curr->prev && !curr->next))
			return (print_serror(curr, redirection, 1), 0);
		curr = curr->next;
	}
	return (1);
}

static void	token_type(t_token *token)
{
	if (ft_strlen(token->word) == 1) // a pipe a redirection or other
	{
		if (!ft_strncmp(token->word, "<", 1)
			|| !ft_strncmp(token->word, ">", 1))
			token->type = redirection;
		else if (!ft_strncmp(token->word, "|", 1))
			token->type = PIPE;
		else
			token->type = word;
	}
	else if (ft_strlen(token->word) == 2) // append, herdoce or other
	{
		if (!ft_strncmp(token->word, ">>", 2)
			|| !ft_strncmp(token->word, "<<", 2))
			token->type = redirection;
		else
			token->type = word;
	}
	else
		token->type = word;
}

static void	token_definer(char **tokens, t_pdata *data)
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
		new_token->next = NULL;
		new_token->prev = NULL;
		token_type(new_token);
		token_add_back(&data->token, new_token);
		i++;
	}
	t_token *curr;
	curr = data->token;
	while (curr)
	{
		printf("%s\n", curr->word);
		curr = curr->next;
	}	
}

void	lexer(char *input, t_pdata *data)
{
	char	*processed_input;
	char	**tokens;

	processed_input = spacing(input, data);
	if (data->traffic)
	{
		printf("minishell: syntax error `quoting'\n");
		free(processed_input);
		return ;
	}
	tokens = ft_split(processed_input);
	token_definer(tokens, data);
	if (!syntax_checker(data))
	{
		free(processed_input);
		twod_free(tokens);
		token_lstclear(&data->token, del);
		return ;
	}
}
