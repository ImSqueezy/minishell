/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:50:17 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/11 20:52:24 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*e_replace_key(t_env *env, char *line, char *key)
{
	t_env	*curr;
	char	*new_line;
	char	*value;

	value = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			value = curr->value;
		curr = curr->next;
	}
	if (!value)
		value = "";
	new_line = malloc((ft_strlen(line) - ft_strlen(key) - 1)
			+ ft_strlen(value) + 1);
	if (!new_line)
		return (NULL);
	new_line = fill_nline(new_line, line, value, ft_strlen(key));
	free(line);
	return (new_line);
}

char	*e_expand(t_env *env, char *line, char *delimiter)
{
	char	*key;
	int		i;

	if (!ft_strcmp(line, delimiter))
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			key = get_key(&line[++i]);
			line = e_replace_key(env, line, key);
			i = 0;
			continue ;
		}
		i++;
	}
	return (line);
}

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

	len = strlen(str);
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

char	*get_heredoc(char *delimiter, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*line;
	int		quotes;

	res = ft_strdup("");
	quotes = has_quotes(delimiter);
	if (quotes)
		delimiter = remove_quotes(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			if (quotes)
				free(delimiter);
			return (res);
		}
		if (!quotes)
			line = e_expand(env, line, delimiter);
		tmp = line; // replace later with set_newstr() for norm
		line = ft_strjoin(line, "\n");
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, line);
		free(line);
		free(tmp);
	}
	return (NULL);
}

void	sigint_heredoc(int sig)
{
	close(STDIN_FILENO);
	g_sigint = sig;
}

char	**get_heredoc_strings(t_token *token, t_env *env)
{
	char	**res;
	int		count;
	int		i;

	signal(SIGINT, sigint_heredoc);
	i = 0;
	count = count_heredocs(token);
	if (count == 0)
		return (NULL);
	res = malloc((count + 1) * sizeof(char *));
	while (i < count + 1)
		res[i++] = NULL;
	i = 0;
	while (token)
	{
		if (token->type == heredoc)
		{
			res[i] = get_heredoc(token->next->word, env);
			i++;
		}
		token = token->next;
	}
	return (res);
}
