/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:16 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/12 15:34:34 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : unset with no options
=================================================================================
Commande unset : supprimer une variable d'environnement
Utilisation : unset [variable]
*/

void	remove_env_var(char *var)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = 0;
	j = 0;
	len = 0;
	while (environ[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var) == 0)
			&& environ[i][ft_strlen(var)] == '=')
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(environ[i]);
	}
	new_env[j] = NULL;
	environ = new_env;
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

int	ft_unset_is_command(t_token_list *tokens)
{
	t_token	*tmp;
	int		i;
	char	*argv[100];

	i = 0;
	tmp = tokens->head;
	while (tmp)
	{
		if (tmp->type == COMMAND && ft_strcmp(tmp->input, "unset") == 0)
		{
			tmp = tmp->next;
			while (tmp && (tmp->type == ARGUMENT || tmp->type == STRING))
			{
				argv[i++] = tmp->input;
				tmp = tmp->next;
			}
			argv[i] = NULL;
			ft_unset(argv);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
