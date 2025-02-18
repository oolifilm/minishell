/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:54:35 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 10:55:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

typedef enum e_token_type
{
    COMMAND,            /*0*/
    ARGUMENT,           /*1*/
    SINGLE_QUOTE,       /*2*/
    DOUBLE_QUOTE,       /*3*/
    REDIRECTION,        /*4*/
    DOUBLE_REDIRECTION, /*5*/
    PIPE,               /*6*/
    DOLLAR,             /*7*/
    EXIT_STATUS,        /*8*/
    ENV_VAR,            /*9*/
    STRING,             /*10*/
}   t_token_type;

typedef struct s_token
{
    char            *input;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

/* Tokenizer functions */
t_token     *tokenize_input(char *input);
void        token_is_command(char *input, int *i, t_token **head,
                t_token **cur, int *is_first_word);
void        assign_quote(char input, t_token **head, t_token **cur);
void        assign_env_var(char *input, int *i, t_token **head, t_token **cur);
void        assign_redirection(char *input, int *i, t_token **head,
                t_token **cur);
void        assign_pipe(char input, t_token **head, t_token **cur);
void        skip_spaces(char *input, int *i);

/* Double quote handling */
char        *handle_double_quoted(char *input, int *i);

#endif
