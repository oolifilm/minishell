/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:54:35 by julien            #+#    #+#             */
/*   Updated: 2025/03/01 10:15:38 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../include/minishell.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

typedef enum e_token_type
{
	COMMAND,            /*0*/
	ARGUMENT,           /*1*/
	SINGLE_QUOTE,       /*2*/
	DOUBLE_QUOTE,       /*3*/
	REDIR_INPUT,        /*4*/
	REDIR_OUTPUT, 		/*5*/
	REDIR_APPEND, 		/*6*/
	HEREDOC, 			/*7*/
	PIPE,               /*8*/
	DOLLAR,             /*9*/
	EXIT_STATUS,        /*10*/
	ENV_VAR,            /*11*/
	STRING,             /*12*/
	REDIR_FILE,         /*13*/
}					t_token_type;

typedef struct s_token
{
	char			*input;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*tokenize_input(char *input);
void				token_is_command(char *input, int *i, t_token **head,
						t_token **cur, int *is_first_word);
void				assign_quote(char input, t_token **head, t_token **cur);
void				assign_env_var(char *input, int *i, t_token **head,
						t_token **cur);
void				assign_redirection(char *input, int *i, t_token **head,
						t_token **cur);
void				assign_pipe(char input, t_token **head, t_token **cur);
void				skip_spaces(char *input, int *i);

char				*expand_var_in_dquotes(char *str);
void				handle_quoted_content(char *input, int *i, t_token **head,
						t_token **cur, char quote_type);

void				free_tokens(t_token *tokens);
char 				*get_token_type_str(t_token_type type);

#endif
