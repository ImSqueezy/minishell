/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:57:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/13 22:41:23 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	key_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void	env_suppressone(t_env **env, t_env **pdata_env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	(1) && (curr = *env, prev = NULL);
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
			{
				*env = curr->next;
				*pdata_env = curr->next;
			}
			env_lstdelone(curr, del);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	unset(t_gdata *shell, char **ar)
{
	bool	permit;
	int		i;

	permit = true;
	i = 1;
	while (ar[i])
	{
		if (ft_isdigit(*ar[i]) || !key_checker(ar[i]) || *ar[i] == '\0')
		{
			printf(UINVALID_IDENTIFIER, ar[i]);
			permit = false;
			shell->exit = 1;
		}
		if (permit)
		{
			env_suppressone(&shell->env, &shell->pdata->env, ar[i]);
			shell->exit = 0;
		}
		i++;
	}
	return (shell->exit);
}
