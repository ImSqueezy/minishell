/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:16:07 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/09 11:22:52 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Parsing/parsing.h"
# include "Execution/execution.h"

typedef struct s_redirections	t_red;
typedef struct s_commands		t_cmd;

typedef struct s_redirections
{
	char	*fname;
	int		type;
	bool	expand;
	bool	ambiguous;
	t_red	*next;
}	t_red;

typedef struct s_commands
{
	char	**cmd;
	int		heredoc_fd;
	t_red	*reds;
	t_cmd	*next;
}	t_cmd;

typedef struct s_gdata
{
	t_cmd	*cmds;
	t_env	*env;
	char	*saved_pwd;
	int		exit;
}	t_gdata;

#endif
