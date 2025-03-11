/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:54:35 by julien            #+#    #+#             */
/*   Updated: 2025/03/11 13:04:41 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../../include/minishell.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

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
}					t_token_list;

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

/*====PARSING====*/
int					is_invalid_first_token(t_token *head);
int					has_consecutive_pipes(t_token *tokens);
int					has_invalid_redirection(t_token *tokens);
// int					has_unclosed_quotes(t_token *tokens);
int					parse_tokens(t_token_list *tokens);
int					has_unclosed_quote(char *input);

#endif
