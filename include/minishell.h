/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:11:12 by leaugust          #+#    #+#             */
/*   Updated: 2025/03/11 12:58:14 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/parsing/executor/exec.h"
# include "../srcs/parsing/tokenizer/tokenizer.h"
# include "../srcs/parsing/parser/parser.h"
# include "../srcs/builtins/builtins.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/*======PARSING======*/

void	exec_command(char *cmd, char **argv);
char	*get_path(char *cmd);
void	ft_free_split(char **tab);

/*======TOKENISATION======*/

void	token_is_command(char *input, int *i, t_token_list *tokens,
			int *is_first_word);
void	assign_pipe(char input, t_token_list *tokens);
void	assign_dollar(char input, t_token_list *tokens);
void	assign_redirection(char *input, int *i, t_token_list *tokens);
void	assign_quote(char input, t_token_list *tokens);
t_token	*add_token(t_token_list *tokens, char *input, t_token_type type);
t_token	*new_token(char *input, t_token_type type);
void	assign_env_var(char *input, int *i, t_token_list *tokens);

void	skip_spaces(char *input, int *i);

#endif