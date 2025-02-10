/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/29 18:46:31 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : env with no options
=================================================================================
Commande env : afficher toutes les variables d'environnement
Utilisation : env
=================================================================================
envp = tableau qui contient toutes les variables d'environnement
*/

int ft_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}
