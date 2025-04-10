/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:31:08 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 14:28:55 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern char	**g_env;
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
	int		i;
	int		arg_count;
	t_token	*current;
	t_token	*redir_token;

	arg_count = 1;
	current = token->next;
	while (current)
	{
		if (current->type == STRING || current->type == ARGUMENT)
			arg_count++;
		current = current->next;
	}
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		return ;
	argv[0] = ft_strdup(token->input);
	i = 1;
	current = token->next;
	while (current)
	{
		if (current->type == STRING || current->type == ARGUMENT)
		{
			argv[i] = ft_strdup(current->input);
			i++;
		}
		current = current->next;
	}
	argv[i] = NULL;
	path = get_path(argv[0]);
	if (path == NULL)
	{
		perror("minishell");
		ft_free_split(argv);
		return ;
	}
	parent = fork();
	if (parent == 0)
	{
		redir_token = token->next;
		while (redir_token)
		{
			if (redir_token->type == REDIR_INPUT
				|| redir_token->type == REDIR_OUTPUT
				|| redir_token->type == REDIR_APPEND
				|| redir_token->type == HEREDOC)
			{
				if (exec_redirection(redir_token) == -1)
				{
					perror("minishell");
					free(path);
					ft_free_split(argv);
					exit(1);
				}
			}
			redir_token = redir_token->next;
		}
		execve(path, argv, g_env);
		perror("minishell");
		free(path);
		ft_free_split(argv);
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
		free(path);
		ft_free_split(argv);
		exit(1);
	}
	free(path);
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
