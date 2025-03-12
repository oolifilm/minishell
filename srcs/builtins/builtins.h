/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:50:01 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/12 15:28:26 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/minishell.h"

extern char	**environ;

/*=====FT_CD=====*/

int			ft_cd(char **argv);
int			handle_command(t_token_list *tokens);

/*=====FT_ECHO=====*/

int			ft_echo(char **argv);
int			ft_echo_is_command(t_token_list *tokens);

/*=====FT_ENV=====*/

int			ft_env(char **envp);
int			ft_env_is_command(t_token_list *tokens);

/*=====FT_EXIT=====*/

int			ft_exit(char **argv);

/*=====FT_EXPORT=====*/

int			add_env(char *var);
int			ft_export(char **argv);

/*=====FT_PWD=====*/

int			ft_pwd(char **argv);

/*=====FT_UNSET=====*/

int			ft_unset(char **argv);
int			ft_unset_is_command(t_token_list *tokens);

#endif