/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:16 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/14 20:02:35 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**g_env;

/*
Ce qui nous est démandé dans le sujet : unset with no options
=================================================================================
Commande unset : supprimer une variable d'g_envnement
Utilisation : unset [variable]
*/

void	remove_env_var(char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (g_env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], var, ft_strlen(var)) == 0
			&& g_env[i][ft_strlen(var)] == '=')
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(g_env[i]);
		i++;
	}
	new_env[j] = NULL;
	i = 0;
	while (g_env[i])
		free(g_env[i++]);
	free(g_env);
	g_env = new_env;
}

int	ft_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(argv[i]);
		i++;
	}
	return (0);
}
