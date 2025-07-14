/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 06:32:55 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 07:02:37 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_heredocs(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == heredoc)
			i++;
		token = token->next;
	}
	return (i);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	has_quotes(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*res_setter(char *final, char *line)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	tmp = final;
	final = ft_strjoin(final, line);
	free(tmp);
	free(line);
	return (final);
}

char	*fill_nline(char *n_line, char *o_line, char *value, int key_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (o_line[i])
	{
		if (o_line[i] == '$' && !k)
		{
			k = 0;
			while (value[k])
				n_line[j++] = value[k++];
			i += key_len + 1;
		}
		if (o_line[i] == '\0')
		{
			n_line[j] = '\0';
			return (n_line);
		}
		n_line[j++] = o_line[i++];
	}
	n_line[j] = '\0';
	return (n_line);
}
