/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:14 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/20 11:34:52 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet: export with no options
=================================================================================
Commande export : ajouter ou modifier une variable d'environnement
Utilisation : export [variable]
=================================================================================
add_env = fonction pour ajouter une variable d'environnement
Peut etre free a la fin ?
*/

int	ft_export(char **argv)
{
	if (argv[1] == NULL)
	{
		printf("export: not enough arguments\n");
		return (1);
	}
    if (add_env(argv[1]) == 1)
        return (1);
    return (0);
}

int	add_env(char *var)
{
	char	**env;
	char	**new_env;
	size_t	env_count;
	size_t	i;

	env_count = 0;
	while (environ[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (new_env == NULL)
	{
		perror("malloc");
		return (1);
	}
	printf("Memory allocated for new_env\n");
	i = 0;
	while (i < env_count)
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[env_count] = var;
	new_env[env_count + 1] = NULL;
	env = new_env;
	return (0);
}
