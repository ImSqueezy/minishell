/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qremoval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:28:19 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 21:58:01 by aouaalla         ###   ########.fr       */
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

char	*str_setter(char *str, char *addition, char n)
{
	char	*tmp;

	tmp = str;
	str = ft_strnjoin(str, addition, n);
	free(tmp);
	return (str);
}

char	*quote_removal(t_token *node)
{
	char	*new;
	char	*mq;
	int		i;

	(1) && (new = NULL, mq = NULL, i = 0);
	while (node->word[i])
	{
		if ((node->word[i] == '\'' || node->word[i] == '"'))
		{
			mq = get_middlequoted(node->word[i], &node->word[i + 1], &i);
			if (mq)
				new = str_setter(new, mq, ft_strlen(mq));
			free(mq);
			i++;
		}
		else
			new = str_setter(new, &node->word[i], 1);
		if (!node->word[i])
			break ;
		i++;
	}
	return (new);
}
