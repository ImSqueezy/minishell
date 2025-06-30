/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/30 22:48:01 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *input, t_pdata *pdata, t_gdata *gdata)
{
	char	*newinput;

	add_history(input);
	if (!lexer(pdata, input))
		return (token_lstclear(&pdata->token, del), gdata->exit = 258, 0);
	expansions_search(pdata, gdata);
	t_token *curr1;
	curr1 = pdata->token;
	while (curr1)
	{
		if (curr1->var != 3)
			curr1->word = quote_removal(curr1, curr1->word);
		curr1 = curr1->next;
	}
	return (token_lstclear(&pdata->token, del), 1);
}

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
