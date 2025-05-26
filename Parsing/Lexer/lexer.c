/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:46:45 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/26 18:54:24 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

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

// temporary (debug)
void	print_tokens(char *world, int type);

void	lexer(char *input, t_pdata *data, t_gdata *gptr)
{
	char	*processed_input;
	char	**tokens;

	processed_input = spacing(input, data);
	tokens = ft_split(processed_input);
	free(processed_input);
	token_definer(tokens, data);
	free(tokens);
	if (!syntax_checker(data, data->traffic))
	{
		token_lstclear(&data->token, del);
		return ;
	}
	re_definer(data->token);
}

/* quick token debuger
	// t_token *curr;
	// curr = data->token;
	// while (curr)
	// {
	// 	print_tokens(curr->word, curr->type);
	// 	printf("- - - - -\n");
	// 	curr = curr->next;
	// }
*/

void	print_tokens(char *word, int type)
{
	printf("token: %s\n", word);
	if (type == 0)
		printf("of type %s\n", "word");
	else if (type == 1)
		printf("of type %s\n", "pipe");
	else if (type == 2)
		printf("of type %s\n", "redirection");
	else if (type == 3)
		printf("of type %s\n", "red_in");
	else if (type == 4)
		printf("of type %s\n", "red_out");
	else if (type == 5)
		printf("of type %s\n", "append");
	else if (type == 6)
		printf("of type %s\n", "heredoc");
	else if (type == 7)
		printf("of type %s\n", "command");
	else if (type == 8)
		printf("of type %s\n", "file");
	else if (type == 9)
		printf("of type %s\n", "delimiter");
}
