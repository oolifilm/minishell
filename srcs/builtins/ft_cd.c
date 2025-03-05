/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/05 15:01:02 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Sujet : cd with only a relative or absolute path
======
cd : changer le répertoire courant vers le répertoire spécifié.
Utilisation : cd [options] [Nom_repertoire]
======
chdir = fonction pour changer le répertoire courant
strerror = Retourne une string d'erreur spécifique à la fonction chdir
*/

int	ft_cd(char **argv)
{
	char	*path;

	if (!argv[1])
	{
		printf("cd: path required\n");
		return (1);
	}
	path = argv[1];
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
