/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:15 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/12 14:44:09 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : pwd with no options
=================================================================================
Commande pwd : afficher le répertoire courant
Utilisation : pwd
=================================================================================
getcwd = fonction pour obtenir le répertoire courant
strerror = fonction pour retourner une string d'erreur spécifique à la fonction getcwd
*/

int	ft_pwd(void)
{
	if (getcwd(g_env->pwd, 1024) == NULL)
	{
		printf("pwd: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
