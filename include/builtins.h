/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:07:20 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/05 14:59:01 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

extern char	**environ;

/*======Function CD======*/

int			ft_cd(char **argv);

/*======Function ECHO======*/

int			ft_echo(char **argv);

/*=======Function ENV======*/

int			ft_env(char **argv);
int			add_env(char *var);

/*======Function EXIT======*/

int			ft_exit(char **argv);

/*======Function EXPORT======*/

int			ft_export(char **argv);

/*======Function PWD======*/

int			ft_pwd(char **argv);

/*======Function UNSET======*/

int			ft_unset(char **argv);

#endif