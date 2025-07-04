/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:13:31 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/04 21:16:13 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env(t_env *head)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (ft_strlen(curr->value) > 0)
		{
			ft_putstr_fd(curr->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(curr->value, 1);
			ft_putchar_fd('\n', 1);
		}
		curr = curr->next;
	}
	return (0);
}
