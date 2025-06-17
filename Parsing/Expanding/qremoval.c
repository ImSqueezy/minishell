/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qremoval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:28:19 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/27 18:28:21 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

char	*get_middlequoted(char target, char *str, int *index)
{
	char	*middlequoted;
	int		i;

	i = 0;
	while (str[i] && str[i] != target)
		i++;
	middlequoted = ft_strndup(str, i);
	*index += i;
	return (middlequoted);
}

char	*quote_removal(t_token *node, char *previous_address)
{
	char	*new;
	char	*mq;
	int		i;

	(1) && (new = NULL, mq = NULL, i = 0);
	while (node->word[i])
	{
		if (node->word[i] == '\'' || node->word[i] == '"')
		{
			mq = get_middlequoted(node->word[i], &node->word[i + 1], &i);
			if (mq)
				new = set_newstr(new, mq, ft_strlen(mq));
			free(mq);
			i++;
		}
		else
			new = set_newstr(new, &node->word[i], 1);
		if (!node->word[i])
			break ;
		i++;
	}
	free(previous_address);
	return (new);
}
