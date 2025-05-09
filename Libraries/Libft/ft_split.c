/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:05:25 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/08 22:01:23 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *p, char sep)
{
	size_t	i;
	size_t	len;
	int		words;
	char	var;

	(1) && (i = 0, var = 0, words = 0, len = ft_strlen(p));
	while (i <= len)
	{
		if (!var && (p[i] == '\'' || p[i] == '"'))
			var = p[i];
		else if (var && p[i] == var)
			var = 0;
		if ((p[i] == sep || p[i] == '\0') && !var)
			words++;
		i++;
	}
	return (words);
}

static char	*initilazing(char const *s, char c, bool in_quote, char quote_char)
{
	char	*p;
	int		i;
	int		len;

	(1) && (i = -1, len = 0);
	while (s[len])
	{
		if ((s[len] == '\'' || s[len] == '\"'))
		{
			if (!in_quote)
				(1) && (in_quote = true, quote_char = s[len]);
			else if (s[len] == quote_char)
				in_quote = false;
		}
		else if (s[len] == c && !in_quote)
			break ;
		len++;
	}
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (++i < len)
		p[i] = s[i];
	p[i] = '\0';
	return (p);
}

static void	ft_free(char **p)
{
	while (*p)
	{
		free(*p);
		p++;
	}
	free(p);
}

char	**ft_split(char const *s, char c)
{
	size_t		words;
	size_t		i;
	bool		quote;
	char		quote_char;
	char		**p;

	if (!s)
		return (0);
	(1) && (i = -1, words = count_words(s, c), quote = 0, quote_char = 0);
	p = (char **)malloc((words + 1) * sizeof(char *));
	if (p == NULL)
		return (0);
	while (++i < words)
	{
		while (*s == c)
			s++;
		p[i] = initilazing(s, c, quote, quote_char);
		if (p[i] == NULL)
			return (ft_free(p), NULL);
		s += ft_strlen(p[i]);
	}
	p[i] = NULL;
	return (p);
}
