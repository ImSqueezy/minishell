/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/21 22:01:39 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

static void	squoting_traffic(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}

static char	*getenv_value(const char *str, t_env *env, int *index)
{
	int		li;
	char	*key;
	char	*value;
	t_env	*curr;

	value = NULL;
	li = 0;
	if (!str[li])
		return (ft_strdup("$"));
	while (str[li] && (str[li] != '$' && str[li] != '\'' && str[li] != '\"'))
		li++;
	key = ft_strndup(str, li);
	curr = env;
	while (curr)
	{
		int var = ft_strcmp(key ,curr->key);
		if (!var)
		{
			value = ft_strdup(curr->value);
			break ;
		}
		curr = curr->next;
	}
	*index += li;
	return (value);
}

static char    *expand(char *word, int *quoting, t_env *env)
{
	int		i;
	int		green_light;
	char	*after_dollar;
	char	*newstr;

	newstr = NULL;
	i = 0;
	green_light = 1;
	while (word[i])
	{
		if (word[i] == '\'')
			squoting_traffic(&green_light);
		if (word[i] == '$' && green_light)
		{
			i++;
			after_dollar = getenv_value(&word[i], env, &i);
			newstr = ft_strjoin(newstr, after_dollar);
			i--;
		}
		else
			newstr = ft_strnjoin(newstr, &word[i], 1);
		i++;
	}
	free(word);
	return (newstr);
}

void	expansions_search(t_pdata *ptr)
{
	t_token	*curr;
	char	*new;
	int		old_tokensize;

	old_tokensize = token_size(ptr->token);
	curr = ptr->token;
	while (curr)
	{
		if (curr->var == 1)
		{
			curr->word = expand(curr->word, &curr->quoting, ptr->env);
			printf("%s\n", curr->word);
		}
		curr = curr->next;
	}
	if (token_size(ptr->token) != old_tokensize)
	expansions_search(ptr);
}
