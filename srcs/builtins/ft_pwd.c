/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:15 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/10 16:50:03 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>

/*
Sujet : pwd with no options
======
Commande pwd : afficher le répertoire courant
Utilisation : pwd
======
getcwd = obtenir le répertoire courant
strerror = Retourner une string d'erreur spécifique à la fonction getcwd
*/

int	ft_pwd(char **argv)
{
	char	buffer[4096];

	(void)argv;
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
