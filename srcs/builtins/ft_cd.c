/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 17:27:26 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>

/*
** get_home_dir : Récupère le chemin du répertoire HOME de l'utilisateur
** @return : Le chemin du HOME ou NULL si la variable HOME n'est pas définie
** Description :
** - Utilise getenv pour obtenir la valeur de la variable d'environnement HOME
** - Affiche une erreur si HOME n'est pas défini
*/

static char	*get_home_dir(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

/*
** get_oldpdw : Récupère le chemin du dernier répertoire visité (OLDPWD)
** @return : Le chemin du OLDPWD ou NULL si la variable OLDPWD n'est pas définie
** Description :
** - Utilise getenv pour obtenir la valeur de la variable d'environnement OLDPWD
** - Affiche une erreur si OLDPWD n'est pas défini
** - Utilisé pour la commande 'cd -'
*/

static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		return (NULL);
	}
	return (oldpwd);
}

/*
** update_pdw : Met à jour les variables d'environnement PWD et OLDPWD
** @return : 0 en cas de succès, 1 en cas d'erreur
** Description :
** - Obtient le répertoire courant avec getcwd
** - Met à jour OLDPWD avec l'ancienne valeur de PWD
** - Met à jour PWD avec le nouveau répertoire courant
** - Gère les erreurs potentielles de getcwd et setenv
*/

static int	update_pwd(void)
{
	char	buffer[4096];
	char	*old_pwd;
	char	*pwd;
	int		ret;

	pwd = getenv("PWD");
	if (pwd)
		old_pwd = ft_strdup(pwd);
	else
		old_pwd = ft_strdup("");
	if (!old_pwd)
		return (1);
	if (!getcwd(buffer, sizeof(buffer)))
	{
		free(old_pwd);
		printf("cd: error getting current directory: %s\n", strerror(errno));
		return (1);
	}
	ret = 0;
	if (setenv("OLDPWD", old_pwd, 1) == -1)
		ret = 1;
	if (setenv("PWD", buffer, 1) == -1)
		ret = 1;
	free(old_pwd);
	return (ret);
}

/*
** ft_cd : Change le répertoire courant
** @param argv : Tableau de chaînes contenant la commande et ses arguments
** @return : 0 en cas de succès, 1 en cas d'erreur
** Description :
** - Sans argument : change vers le répertoire HOME
** - Avec '-' : change vers le dernier répertoire visité (OLDPWD)
** - Avec un chemin : change vers le chemin spécifié (relatif ou absolu)
** - Met à jour PWD et OLDPWD après chaque changement réussi
*/

int	ft_cd(char **argv)
{
	char	*path;

	if (!argv[1])
	{
		path = get_home_dir();
		if (!path)
			return (1);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = get_oldpwd();
		if (!path)
			return (1);
		printf("%s\n", path);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (update_pwd());
}

/*
PWD ne marche pas ?
CD marche
*/

int	handle_command(t_token_list *tokens)
{
	t_token	*tmp;
	char	*args[3];

	args[0] = "";
	args[1] = NULL;
	args[2] = NULL;
	tmp = tokens->head;
	if (tmp && tmp->type == CMD)
	{
		if (ft_strcmp(tmp->input, "cd") == 0)
		{
			args[0] = "cd";
			if (tmp->next)
				args[1] = tmp->next->input;
			ft_cd(args);
		}
		else if (ft_strcmp(tmp->input, "pwd") == 0)
			ft_pwd(NULL);
	}
	return (0);
}
