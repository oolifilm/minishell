/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:16 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/10 10:21:45 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : unset with no options
=================================================================================
Commande unset : supprimer une variable d'environnement
Utilisation : unset [variable]
*/

int	ft_unset(char **argv)
{
	char	**env;
	char	**env_to_remove;
	size_t	len;

	env = environ;
	env_to_remove = env;
	len = ft_strlen(argv[1]);
	while (*env)
	{
		if (ft_strncmp(*env, argv[1], len) == 0 && (*env)[len] == '=')
		{
			while (*env_to_remove)
			{
				*env_to_remove = *(env_to_remove + 1);
				env_to_remove++;
			}
			break ;
		}
		env++;
	}
	return (0);
}
