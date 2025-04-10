/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 12:41:54 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**g_env;

/*
Sujet : env with no options
======
Commande env : afficher toutes les variables d'g_envnement
Utilisation : env
======
envp = tableau qui contient toutes les variables d'g_envnement
*/

int	ft_env(char **argv)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		printf("[ERROR] env: no options\n");
		return (1);
	}
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	return (0);
}
