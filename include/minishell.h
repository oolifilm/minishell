/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:11:12 by leaugust          #+#    #+#             */
/*   Updated: 2025/04/09 11:03:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

extern char			**environ;

/***********************************/
/*==========TOKEN STRUCT==========*/
/*********************************/

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	HEREDOC,
	PIPE,
	DOLLAR,
	EXIT_STATUS,
	ENV_VAR,
	STRING,
	REDIR_FILE,
}					t_token_type;

typedef struct s_token
{
	char			*input;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_list
{
	t_token			*head;
	t_token			*cur;
	int				size;
}					t_token_list;

/************************************/
/*==========PARSER STRUCT==========*/
/**********************************/

typedef struct s_cmd
{
	char			**args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

/********************************/
/*==========TOKENIZER==========*/
/******************************/

/*=====DOUBLE_QUOTED=====*/

char				*expand_var_in_dquotes(char *str);

/*=====HERE_DOC=====*/

void				handle_heredoc(char *input, int *i, t_token **head,
						t_token **cur);

/*=====TOKEN_COMMAND=====*/

void				token_is_command(char *input, int *i, t_token_list *tokens,
						int *is_first_word);
void				assign_env_var(char *input, int *i, t_token_list *tokens);

/*=====TOKEN__IS_REDIR=====*/

void				assign_redirection(char *input, int *i,
						t_token_list *tokens);

/*=====TOKEN_OPERATORS=====*/

void				assign_pipe(char input, t_token_list *tokens);
void				assign_dollar(char input, t_token_list *tokens);

/*=====TOKEN_QUOTES=====*/

void				handle_quoted_content(char *input, int *i,
						t_token_list *tokens, char quote_type);

/*=====TOKEN_UTILS=====*/

t_token				*new_token(char *input, t_token_type type);
t_token				*add_token(t_token_list *tokens, char *input,
						t_token_type type);
void				skip_spaces(char *input, int *i);
void				free_tokens(t_token_list *tokens_list);
char				*get_token_type_str(t_token_type type);

/*=====TOKENIZER=====*/

t_token_list		*tokenize_input(char *input);
t_token_list		*init_token_list(void);

/******************************/
/*==========PARSING==========*/
/****************************/

int					parse_tokens(t_token_list *tokens);
int					is_invalid_first_token(t_token *head);
int					has_consecutive_pipes(t_token *tokens);
int					has_invalid_redirection(t_token *tokens);
// int					has_unclosed_quotes(t_token *tokens);
int					has_unclosed_quote(char *input);

/***************************/
/*==========EXEC==========*/
/*************************/

/*======EXEC======*/

void				exec_command(char *cmd, char **argv);
char				*get_path(char *cmd);
void				ft_free_split(char **split);

/*======REDIR EXEC======*/

int					exec_redirection(t_token *token);

/*******************************/
/*==========BUILTINS==========*/
/*****************************/
/*=====FT_CD=====*/

int					ft_cd(char **argv);
int					handle_command(t_token_list *tokens);

/*=====FT_ECHO=====*/

int					ft_echo(char **argv);
int					ft_echo_is_command(t_token_list *tokens);

/*=====FT_ENV=====*/

int					ft_env(char **envp);
int					ft_env_is_command(t_token_list *tokens);

/*=====FT_EXIT=====*/

int					ft_exit(char **argv);

/*=====FT_EXPORT=====*/

int					add_env(char *var);
int					ft_export(char **argv);

/*=====FT_PWD=====*/

int					ft_pwd(char **argv);

/*=====FT_UNSET=====*/

int					ft_unset(char **argv);
int					ft_unset_is_command(t_token_list *tokens);

/*=====BUILTIN_UTILS=====*/

int					is_valid_env_var(const char *var);
void				print_env_var(char *var);
int					compare_vars(const void *a, const void *b);
int					print_sorted_env(void);

/*=====SIGNALS=====*/

void				sigint_handler(int sig);
void				set_sig_action(void);

#endif