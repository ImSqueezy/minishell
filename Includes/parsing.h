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

/*
    - Libft has:
        * unistd
        * stdlib
        * limits
		* stdbool
*/
# include "../Libraries/Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

#define SYNTAX_ERROR "minishell: syntax error near unexpected token"

typedef struct s_token t_token;

typedef enum enum_token_type
{
	word,
	PIPE,
	redirection,
}	t_etype;

typedef struct s_token
{
    char    *word;
    int     type;
    t_token *next;
	t_token	*prev;
}   t_token;	

typedef struct parsing
{
	bool	traffic;
	char	quote;
	char	prev;
	t_token	*token;
}	t_pdata;

char	*spacing(const char *p, t_pdata *data);
size_t	straddlen(const char *p, size_t old_len, t_pdata *data);
int		quoting_traffic(char c, t_pdata *data);
int		isred(char c);
int		isop(char c);

void	twod_free(char **p);
void	del(void *ptr);
void	token_lstdelone(t_token *lst, void (*del)(void *));
void	token_lstclear(t_token **lst, void (*del)(void *));
void	token_add_back(t_token **lst, t_token *new);
void	lexer(char *input, t_pdata *data);
int	is_whitespace(char c);

#endif
