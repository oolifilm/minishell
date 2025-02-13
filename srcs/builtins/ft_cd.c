/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/29 18:06:29 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : cd with only a relative or absolute path
=================================================================================
Commande cd : changer le répertoire courant vers le répertoire spécifié.
Utilisation : cd [options] [Nom_repertoire]
=================================================================================
chdir = fonction pour changer le répertoire courant
strerror = fonction pour retourner une string d'erreur spécifique à la fonction chdir
*/

int	ft_cd(char **argv)
{
    char *path;

    if(!argv[1])
    {
        printf("cd: path required\n");
        return (1);
    }
    path = argv[1];
    if(chdir(path) == -1)
    {
        printf("cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
    return (0);
}
