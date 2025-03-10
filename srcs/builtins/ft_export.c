/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:14 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/10 10:46:29 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si une variable d'environnement est valide
** @param var: la chaîne à vérifier (ex: "PATH=/bin:/usr/bin")
** @return: 1 si valide, 0 sinon
**
** Format valide:
** - Doit commencer par une lettre ou un underscore
** - Suivi de lettres, chiffres ou underscores
** - Doit contenir un signe égal
** - Peut avoir n'importe quelle valeur après le égal
** Exemples valides: "PATH=/usr/bin", "HOME=/Users/julien", "_TEST=123"
** Exemples invalides: "1VAR=test", "VAR", "=value"
*/
static int is_valid_env_var(const char *var)
{
	int i;

	if (!var || !*var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (var[i] == '=');
}

/*
** Remplace une variable d'environnement existante par une nouvelle valeur
** @param var: la nouvelle variable (ex: "PATH=/nouveau/chemin")
** @return: 
**   0  : si la variable a été remplacée avec succès
**   1  : si erreur d'allocation mémoire
**   -1 : si la variable n'existe pas dans l'environnement
**
** Exemple:
** Si environ contient "PATH=/usr/bin" et on appelle avec var="PATH=/bin"
** alors environ sera modifié pour contenir "PATH=/bin"
*/
static int replace_env_var(char *var)
{
	int i;
	size_t var_len;
	char *equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (0);
	var_len = equal_sign - var;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, var_len) == 0 
			&& environ[i][var_len] == '=')
		{
			free(environ[i]);
			environ[i] = ft_strdup(var);
			if (!environ[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (-1);
}

/*
** Libère un tableau de chaînes de caractères et ses éléments
** @param env: le tableau à libérer
** @return: void
*/
static void free_env_array(char **env)
{
	size_t i;

	if (!env)
		return;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

/*
** Initialise un nouveau tableau d'environnement
** @param new_env: pointeur vers le nouveau tableau à créer
** @param count: pointeur vers le compteur d'éléments
** @return: 1 si erreur, 0 si succès
*/
static int init_new_env(char ***new_env, size_t *count)
{
	*count = 0;
	while (environ[*count])
		(*count)++;
	*new_env = malloc(sizeof(char *) * (*count + 2));
	return (*new_env == NULL);
}

/*
** Copie l'environnement actuel et ajoute une nouvelle variable
** @param new_env: le nouveau tableau d'environnement
** @param var: la variable à ajouter
** @param count: nombre de variables actuelles
** @return: 1 si erreur, 0 si succès
*/
static int copy_and_add_var(char **new_env, char *var, size_t count)
{
	size_t i;

	i = 0;
	while (i < count && environ[i])
	{
		if (!(new_env[i] = ft_strdup(environ[i])))
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (1);
		}
		i++;
	}
	if (!(new_env[count] = ft_strdup(var)))
	{
		while (i > 0)
			free(new_env[--i]);
		free(new_env);
		return (1);
	}
	new_env[count + 1] = NULL;
	return (0);
}

/*
** Ajoute ou met à jour une variable d'environnement
** @param var: la variable à ajouter (format: NAME=VALUE)
** @return: 0 si succès, 1 si erreur
*/
int	add_env(char *var)
{
	char	**new_env;
	char	**old_env;
	size_t	env_count;

	if (!is_valid_env_var(var))
		return (printf("export: '%s': not a valid identifier\n", var), 1);
	if (replace_env_var(var) != -1)
		return (0);
	if (init_new_env(&new_env, &env_count))
		return (1);
	if (copy_and_add_var(new_env, var, env_count))
		return (1);
	old_env = environ;
	environ = new_env;
	free_env_array(old_env);
	return (0);
}

/*
** Implémente la commande 'export' du shell
** @param argv: tableau des arguments de la commande
**             argv[0] = "export"
**             argv[1..n] = variables à exporter
** @return: 0 si succès, 1 si erreur
**
** Deux comportements :
** 1. Sans argument (argv[1] = NULL):
**    - Affiche toutes les variables d'environnement avec "declare -x"
**    Exemple: export -> affiche "declare -x PATH=/usr/bin"
**
** 2. Avec arguments:
**    - Ajoute ou met à jour chaque variable dans l'environnement
**    Exemple: export PATH=/bin USER=john
*/
int	ft_export(char **argv)
{
	int i;

	if (!argv[1])
	{
		i = 0;
		while (environ[i])
		{
			printf("declare -x %s\n", environ[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (add_env(argv[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
