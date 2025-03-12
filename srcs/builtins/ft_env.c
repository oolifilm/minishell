/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:09 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:17 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Sujet : env with no options
======
Commande env : afficher toutes les variables d'environnement
Utilisation : env
======
envp = tableau qui contient toutes les variables d'environnement
*/

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	ft_env_is_command(t_token_list *tokens)
{
	t_token	*tmp;
	int		i;
	char	*argv[100];

	i = 0;
	tmp = tokens->head;
	while (tmp)
	{
		if (tmp->type == COMMAND && ft_strcmp(tmp->input, "env") == 0)
		{
			tmp = tmp->next;
			while (tmp && (tmp->type == ARGUMENT || tmp->type == STRING))
			{
				argv[i++] = tmp->input;
				tmp = tmp->next;
			}
			argv[i] = NULL;
			ft_env(environ);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
