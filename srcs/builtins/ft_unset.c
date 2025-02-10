/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:16 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/30 12:13:58 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (ft_strnmp(*env, argv[1], len) == 0 && (*env)[len] == '=')
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
