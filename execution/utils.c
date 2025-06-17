/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:51:11 by yettalib          #+#    #+#             */
/*   Updated: 2025/06/17 15:58:11 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int    ft_strcmp(char *s1, char *s2)
{
    size_t    i;

    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}


static int	count_words(const char *s, char c)
{
	int	count_w;
	int	i;

	count_w = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count_w += 1;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count_w);
}

static char	*copy_w(const char *s, char c)
{
	size_t	i;
	char	*word_ch;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word_ch = (char *)malloc(i + 1);
	if (!word_ch)
		return (0);
	ft_strlcpy(word_ch, s, i + 1);
	return (word_ch);
}

static void	free1(char **resulta)
{
	size_t	i;

	i = 0;
	while (resulta[i])
	{
		free(resulta[i]);
		i++;
	}
	free(resulta);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	char	**result;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		result[i] = copy_w(s, c);
		if (!result[i])
			return (free1(result), NULL);
		s += ft_strlen(result[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
