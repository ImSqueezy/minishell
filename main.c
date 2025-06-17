/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/17 16:17:29 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/parsing.h"

int	parser(char *input, t_pdata *pdata)
{
	t_gdata	*gdata;
	char	*newinput;

	add_history(input);
	lexer(input, pdata, gdata);
	expansions_search(pdata);
	token_lstclear(&pdata->token, del);
	return (1);
}

void	free_minishell(t_pdata *ptr)
{
	token_lstclear(&ptr->token, del);
	env_lstclear(&ptr->env, del);
}

int	main(int ac, char **av, char **env)
{
	t_pdata	pdata;
	char	*read;

	pdata.env = NULL;
	pdata.token = NULL;
	get_env(&pdata.env, env);
	while (1)
	{
		read = readline("$");
		if (!read)
			return (printf("minishell exited!\n"), free_minishell(&pdata), 0);
		parser(read, &pdata);
	}
	return (0);
}
