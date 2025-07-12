/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:46:45 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/12 18:52:40 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	syntax_checker(t_pdata *data, int quoting_flag)
{
	t_token	*curr;

	if (quoting_flag)
		return (printf("minishell: syntax error `quoting'\n"), 0);
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

int	lexer(t_pdata *data, char *input)
{
	char	*processed_input;
	char	**tokens;

	processed_input = spacing(input, data);
	tokens = ft_split(processed_input);
	free(processed_input);
	token_definer(tokens, data);
	ft_free(tokens);
	if (!syntax_checker(data, data->traffic))
		return (0);
	re_definer(data->token);
	return (1);
}
