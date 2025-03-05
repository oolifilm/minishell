/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:54:35 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 14:57:02 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"

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

t_token_list		*tokenize_input(char *input);
void				assign_quote(char input, t_token_list *tokens);
void				assign_env_var(char *input, int *i, t_token_list *tokens);
void				assign_redirection(char *input, int *i,
						t_token_list *tokens);
void				skip_spaces(char *input, int *i);

char				*expand_var_in_dquotes(char *str);
void				handle_quoted_content(char *input, int *i,
						t_token_list *tokens, char quote_type);

void				free_tokens(t_token_list *tokens_list);
char				*get_token_type_str(t_token_type type);

t_token_list		*init_token_list(void);

#endif
