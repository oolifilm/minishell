/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:11:12 by leaugust          #+#    #+#             */
/*   Updated: 2025/02/11 14:59:51 by jbanchon         ###   ########.fr       */
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
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECTION,
	DOUBLE_REDIRECTION,
	PIPE,
	DOLAR,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	struct s_token	type;
	struct s_token	*next;
}					t_token;

/*=======================================PARSING==========================================*/

void				exec_command(char *cmd, char **argv);
char				*get_path(char *cmd);
void				ft_free_split(char **tab);

#endif