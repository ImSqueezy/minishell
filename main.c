/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/03 12:44:40 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_pdata *ptr)
{
	token_lstclear(&ptr->token, del);
	env_lstclear(&ptr->env, del);
}

void	execute(t_gdata	*data)
{
	(void)data;
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_pdata	pdata;
	t_gdata	gdata;
	char	*read;

	pdata.env = NULL;
	pdata.token = NULL;
	gdata.exit = 0;
	get_env(&pdata.env, env);
	while (1)
	{
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n"), free_minishell(&pdata), 0);
		if (parser(read, &pdata, &gdata))
			execute(&gdata);
	}
	return (0);
}
