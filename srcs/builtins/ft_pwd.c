/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:15 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/05 15:02:40 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Sujet : pwd with no options
======
Commande pwd : afficher le répertoire courant
Utilisation : pwd
======
getcwd = obtenir le répertoire courant
strerror = Retourner une string d'erreur spécifique à la fonction getcwd
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
