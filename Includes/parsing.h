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
	word, // 0
	PIPE, // 1
	redirection, // 2
	red_in, // 3
	red_out, // 4
	append, // 5
	heredoc, // 6
	command, // 7
	file, // 8
	delimiter, // 9
}	t_etype;

typedef struct s_token
{
    char    *word;
    int     type;
	int		quoting;	
	int		var;
    t_token *next;
	t_token	*prev;
}   t_token;	

typedef struct s_env t_env;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

typedef struct parsing
{
	bool	traffic;
	char	quote;
	char	prev;
	t_token	*token;
	t_env	*env;
}	t_pdata;

typedef	struct minishell
{
	char	*first;
	char	**cmd;
	int		fd_in;
	int		fd_out;
	t_env 	*env;
}	t_gdata;

char	*spacing(const char *p, t_pdata *data);
size_t	straddlen(const char *p, size_t old_len, t_pdata *data);
int		quoting_traffic(char c, t_pdata *data);
int		isred(char c);
int		isop(char c);
int		is_whitespace(char c);

void	twod_free(char **p);
void	del(void *ptr);
void	token_lstdelone(t_token **head, t_token *lst, void (*del)(void *));
void	token_lstclear(t_token **lst, void (*del)(void *));
void	token_add_back(t_token **lst, t_token *new);
void	lexer(char *input, t_pdata *data, t_gdata *ptr);
void	re_definer(t_token *head);
void	token_definer(char **tokens, t_pdata *data);
void	get_env(t_env **ptr, char **env);
int		env_size(t_env *env);
void	print_tokens(char *word, int type);

void	expansions_search(t_pdata *ptr);
char	*ft_strnjoin(const char *s1, const char *s2, int n);
int		token_size(t_token *ptr);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, int n);

void	env_lstclear(t_env **head, void (*del)(void *));
void	env_lstdelone(t_env *node, void (*del)(void *));

#endif
