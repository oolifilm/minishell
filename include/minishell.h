/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:11:12 by leaugust          #+#    #+#             */
/*   Updated: 2025/02/12 14:59:11 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	COMMAND,            /*0*/
	OPTION,             /*1*/
	SINGLE_QUOTE,       /*2*/
	DOUBLE_QUOTE,       /*3*/
	REDIRECTION,        /*4*/
	DOUBLE_REDIRECTION, /*5*/
	PIPE,               /*6*/
	DOLLAR,             /*7*/
	OUTFILE,            /*8*/
	ARGUMENT,           /*9*/
}					t_token_type;

typedef struct s_token
{
	char			*input;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_info
{
	t_token			**head;
	t_token			**cur;
	int				*is_first;
}					t_token_info;

/*=======================================PARSING==========================================*/

void				exec_command(char *cmd, char **argv);
char				*get_path(char *cmd);
void				ft_free_split(char **tab);

/*=======================================TOKENISATION==========================================*/

void				token_is_command(char *input, int *i, t_token_info *info);
t_token				*tokenize_input(char *input);
void				assign_dollar(char input, t_token **head, t_token **cur);
void				assign_pipe(char input, t_token **head, t_token **cur);
void				assign_redirection(char *input, int *i, t_token **head,
						t_token **cur);
void				assign_quote(char input, t_token **head, t_token **cur);
t_token				*add_token(t_token **head, t_token **cur, char *input,
						t_token_type type);
t_token				*new_token(char *input, t_token_type type);
void				token_is_outfile(char *input, int *i, t_token **head,
						t_token **cur);
t_token				*tokenize_input(char *input);
void				free_tokens(t_token *tokens);

#endif