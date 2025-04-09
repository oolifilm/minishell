/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:31:08 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/09 14:43:26 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction qui execute une commande.
Elle prend en parametre le nom de la commande.
======
On va chercher le PATH de la commande avec la fonction get_path.
On a un processus parent qui fork un processus enfant.
Le processus enfant va executer la commande.
Tandis que le processus parent attend la fin de l'execution de la commande.
*/

void	exec_command(t_token *token)
{
	pid_t	parent;
	char	*path;
	char	**argv;

	argv = ft_split(token->input, ' ');
	path = get_path(argv[0]);
	if (path == NULL)
	{
		perror("minishell");
		exit(1);
	}
	parent = fork();
	if (parent == 0)
	{
		execve(path, argv, environ);
		perror("minishell");
		exit(1);
	}
	else if (parent > 0)
	{
		waitpid(parent, NULL, 0);
		printf("command executed\n");
	}
	else
	{
		perror("minishell");
		exit(1);
	}
	ft_free_split(argv);
}

/*
Fonction qui va chercher le PATH de la commande.
Elle prend en parametre le nom de la commande.
======
On va utiliser la fonction getenv pour recuperer le PATH.
On split le PATH pour recuperer chaque chemin et verifier
si la commande existe dans un de ces repertoires.
On va parcourir le PATH pour chercher le chemin de la commande.
Fonction	access(void) avec F_OK permet de verifier si le chemin existe.
*/

char	*get_path(char *cmd)
{
	char	*path;
	char	*path_cmd;
	char	**path_split;
	int		i;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_split = ft_split(path, ':');
	if (path_split == NULL)
		return (NULL);
	i = 0;
	while (path_split[i])
	{
		path_cmd = ft_strjoin(path_split[i], "/");
		path_cmd = ft_strjoin(path_cmd, cmd);
		//printf("Path cmd: %s\n", path_cmd);
		if (access(path_cmd, F_OK) == 0)
			return (ft_free_split(path_split), path_cmd);
		free(path_cmd);
		i++;
	}
	return (ft_free_split(path_split), NULL);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
