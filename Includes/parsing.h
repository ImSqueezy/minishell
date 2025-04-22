/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:39:54 by aouaalla          #+#    #+#             */
/*   Updated: 2025/04/21 21:39:55 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <termios.h>

typedef struct s_env t_env;

typedef enum e_token_type
{
	t_word,
	t_pipe,
	t_less
}	t_type;

typedef struct s_fd
{
	int	fd1;
	int	fd2;
}	t_fd;

typedef struct s_env
{
	char	*key;
	char	*val;
	char	index;
	t_env	*env;
}	t_env;

#endif
