/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:05:25 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/12 18:56:30 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	count_words(const char *p)
{
	size_t	i;
	size_t	len;
	int		words;
	char	var;
	char	previous;

	i = 0;
	var = 0;
	words = 0;
	previous = p[i];
	len = ft_strlen(p);
	while (i <= len)
	{
		if (!var && (p[i] == '\'' || p[i] == '"'))
			var = p[i];
		else if (p[i] == var)
			var = 0;
		if (!var && (is_whitespace(p[i]) || p[i] == '\0')
			&& !is_whitespace(previous))
			words++;
		previous = p[i];
		i++;
	}
	return (words);
}

static char	*initilazing(char const *s, bool in_quote, char quote_char)
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
		else if (is_whitespace(s[len]) && !in_quote)
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

void	ft_free(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p[i])
	{
		if (p[i])
			free(p[i]);
		i++;
	}
	free(p);
}

char	**ft_split(char const *s)
{
	size_t		words;
	size_t		i;
	bool		quote;
	char		quote_char;
	char		**p;

	if (!s)
		return (0);
	(1) && (i = -1, words = count_words(s));
	quote = 0;
	quote_char = 0;
	p = (char **)malloc((words + 1) * sizeof(char *));
	if (p == NULL)
		return (0);
	while (++i < words)
	{
		while (is_whitespace(*s))
			s++;
		p[i] = initilazing(s, quote, quote_char);
		if (p[i] == NULL)
			return (ft_free(p), NULL);
		s += ft_strlen(p[i]);
	}
	p[i] = NULL;
	return (p);
}
