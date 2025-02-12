/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:11:12 by leaugust          #+#    #+#             */
/*   Updated: 2025/02/12 12:32:05 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtins.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION,
	DOUBLE_REDIRECTION,
	PIPE,
	DOLLAR,
}					t_token_type;

typedef struct s_token
{
	char			*input;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

/*=======================================PARSING==========================================*/

void				exec_command(char *cmd, char **argv);
char				*get_path(char *cmd);
void				ft_free_split(char **tab);

/*=======================================TOKENISATION==========================================*/

void				token_is_command(char *input, int *i, t_token **head,
						t_token **cur);
t_token				*tokenize_input(char *input);
void				assign_dollar(char input, t_token **head, t_token **cur);
void				assign_pipe(char input, t_token **head, t_token **cur);
void				assign_redirection(char *input, int *i, t_token **head,
						t_token **cur);
void				assign_quote(char input, t_token **head, t_token **cur);
t_token				*add_token(t_token **head, t_token **cur, char *input,
						t_token_type type);
t_token				*new_token(char *input, t_token_type type);

#endif