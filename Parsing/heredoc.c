/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:50:17 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 19:36:09 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			free(key);
			i = 0;
			continue ;
		}
		i++;
	}
	return (line);
}

char	*get_heredoc(char *delimiter, t_env *env)
{
	char	*res;
	char	*line;
	char	*tmp;
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
			return (free(line), res);
		}
		if (!quotes)
			line = e_expand(env, line, delimiter);
		res = res_setter(res, line);
	}
	return (NULL);
}

void	sigint_heredoc(int sig)
{
	close(STDIN_FILENO);
	g_sigint = sig;
}

char	**get_heredoc_strings(t_token *token, t_env *env, int i)
{
	char	**res;
	int		count;

	signal(SIGINT, sigint_heredoc);
	count = count_heredocs(token);
	if (count == 0)
		return (NULL);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < count + 1)
		res[i++] = NULL;
	i = 0;
	while (token)
	{
		if (token->type == heredoc)
		{
			res[i] = get_heredoc(token->next->word, env);
			if (g_sigint)
				return (ft_free(res), NULL);
			i++;
		}
		token = token->next;
	}
	return (res);
}
