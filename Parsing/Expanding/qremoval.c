/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qremoval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:28:19 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/04 21:25:44 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * n + 1);
	if (!new)
		return (NULL);
	i = ft_strlcpy(new, s1, n + 1);
	return (new);
}

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

int	check_mate(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*quote_removal(t_token *node, char *previous_address)
{
	char	*new;
	char	*mq;
	int		i;

	(1) && (new = NULL, mq = NULL, i = 0);
	while (node->word[i])
	{
		if ((node->word[i] == '\'' || node->word[i] == '"')
			&& check_mate(&node->word[i], node->word[i]) && node->quoting != -3)
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
	// free(previous_address); if enabled it suppresses the leaks, but gives double free
	return (new);
}
