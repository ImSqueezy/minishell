/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:16:07 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 21:54:47 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Parsing/parsing.h"
# include "Execution/execution.h"
# include <signal.h>

typedef struct s_redirections	t_red;
typedef struct s_commands		t_cmd;

typedef struct s_redirections
{
	char	*fname;
	int		type;
	bool	expand;
	bool	ambiguous;
	char	*heredoc_string;
	t_red	*next;
}	t_red;

typedef struct s_commands
{
	char	**cmd;
	t_red	*reds;
	t_cmd	*next;
}	t_cmd;

typedef struct s_gdata
{
	t_cmd	*cmds;
	t_env	*env;
	char	*saved_pwd;
	int		*pids;
	int		saved_stdin;
	int		saved_stdout;
	int		exit;
	t_pdata	*pdata;
}	t_gdata;

void	data_clear(t_gdata *gdata, t_pdata *pdata, char *read);
int		is_spaces(char *str);
void	sigint_handler(int sig);
void	free_minishell(t_pdata *ptr, char *read_line);

#endif