/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:15:49 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 13:23:00 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../../include/minishell.h"
# include "../parser.h"

/*typedef struct s_token
{
	char			*input;
	struct s_token	*next;
}					t_token;
                    */

/*=======================================EXEC==========================================*/

void				exec_command(char *cmd, char **argv);
char				*get_path(char *cmd);
void                ft_free_split(char **split);

/*=======================================REDIR EXEC==========================================*/

int                  exec_redirection(t_token *token);


#endif