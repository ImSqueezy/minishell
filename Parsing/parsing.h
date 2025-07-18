/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:39:54 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 22:58:59 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int						g_sigint;
typedef struct s_redirections	t_red;
typedef struct s_gdata			t_gdata;
typedef struct s_commands		t_cmd;
typedef struct s_token			t_token;
typedef struct s_env			t_env;

# define EINVALID_IDENTIFIER "minishell: export: `%s': not a valid identifier\n"
# define UINVALID_IDENTIFIER "minishell: unset: `%s': not a valid identifier\n"
# define SYNTAX_ERROR "minishell: syntax error near unexpected token"
# define REDS_COUNT 1
# define CMDS_COUNT 0

typedef enum enum_token_type
{
	word,
	PIPE,
	redirection,
	red_in,
	red_out,
	append,
	heredoc,
	command,
	file,
	delimiter,
}	t_etype;

typedef struct s_token
{
	char	*word;
	int		type;
	int		var;
	int		quoting;	
	bool	split_permit;
	t_token	*next;
	t_token	*prev;
}	t_token;

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
	char	**heredoc_strs;
	int		heredoc_count;
	t_token	*token;
	t_env	*env;
}	t_pdata;

int		parser(char *input, t_pdata *pdata, t_gdata *gdata);
char	*spacing(const char *p, t_pdata *data);
size_t	straddlen(const char *p, size_t old_len, t_pdata *data);
int		quoting_traffic(char c, t_pdata *data);
int		isred(char c);
int		isop(char c);
int		is_whitespace(char c);

int		count_heredocs(t_token *token);
char	*remove_quotes(char *str);
int		has_quotes(char *delimiter);
char	*res_setter(char *final, char *line);
char	*fill_nline(char *n_line, char *o_line, char *value, int key_len);

void	del(void *ptr);
void	token_lstdelone(t_token **head, t_token *lst, void (*del)(void *));
void	pdata_lstclear(t_pdata *ptr, void (*del)(void *));
void	token_addback(t_token **lst, t_token *new);
int		lexer(t_pdata *data, char *input);
void	re_definer(t_token *head);
void	token_definer(char **tokens, t_pdata *data);
void	get_env(t_env **ptr, char **env);
int		env_size(t_env *env);

void	expansions_search(t_pdata *pdata, t_gdata *gdata);
void	quote_suppression(t_token *head);
void	export_threater(t_token	*head);
void	equoting_traffic(char quote, char *prev);
char	*preserve_value(char *str);
char	*epreserve_key(char *str, int i, int j);
int		valid_identifier(char *key);
char	*ft_strnjoin(const char *s1, const char *s2, int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, int n);
int		_isred(char c);
void	suppress_emptytokens(t_token **head);

char	*get_value(char *p);
char	*get_key(char *p);
t_env	*env_addnew(char *key, char *value);
int		empty_value(char *str);
void	env_addback(t_env **head, t_env *new);
void	env_lstclear(t_env **head, void (*del)(void *));
void	env_lstdelone(t_env *node, void (*del)(void *));
void	token_insert_after(t_token *current, t_token *new_node);
t_token	*sub_token_addnew(char *word, t_token *prev);
char	*getenv_value(t_pdata *ptr, const char *str, int *index, int exit_st);

char	*str_setter(char *str, char *addition, char n);
char	*quote_removal(t_token *node);

void	cmd_addback(t_cmd **lst, t_cmd *new);
void	red_addback(t_red **lst, t_red *new);
t_cmd	*cmd_addnew(t_token *lst, t_pdata *data);
int		define_ftype(int type);
int		cmds_reds_counter(t_token *cmd, int count_flag);
char	**get_heredoc_strings(t_token *token, t_env *env, int i);
void	tcmd_lstclear(t_cmd *lst);

#endif