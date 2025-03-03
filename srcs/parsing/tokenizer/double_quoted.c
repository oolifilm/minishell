/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:39:41 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 13:11:39 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction pour récupérer le nom de la variable d'environnement
1. Avance jusqu'au prochain caractère après le '$'.
2. Récupère le nom de la variable d'environnement.
3. Retourne la position actuelle.
*/

static int	get_env_var_name(char *input, int j, char *var_name)
{
	int	var_len;

	var_len = 0;
	j++;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
	{
		var_name[var_len] = input[j];
		var_len++;
		j++;
	}
	var_name[var_len] = '\0';
	return (j);
}

/*
Fonction pour calculer la longueur de la chaîne entre quotes.
1. Avance jusqu'à la quote fermante.
2. Si un '$' est trouvé, récupère le nom de la variable d'environnement.
3. Ajoute la longueur de la valeur de la variable d'environnement.
4. Retourne la longueur totale.
*/

static int	cal_quoted_len(char *input, int j)
{
	int		len;
	char	var_name[256];
	char	*env_value;

	len = 0;
	while (input[j] && input[j] != '"')
	{
		if (input[j] == '$' && input[j + 1])
		{
			j = get_env_var_name(input, j, var_name);
			env_value = getenv(var_name);
			if (env_value)
				len += ft_strlen(env_value);
			j--;
		}
		else
			len++;
		j++;
	}
	return (len);
}

/*
Fonction pour remplir le contenu entre quotes.
1. Avance jusqu'à la quote fermante.
2. Si un '$' est trouvé, récupère le nom de la variable d'environnement.
3. Si la variable d'environnement existe, ajoute sa valeur.
4. Sinon, ajoute le caractère tel quel.
5. Retourne la position actuelle.
*/

// /!\ Fonction qui doit etre reduite

static void	fill_quoted_content(char *input, char *result, int *i)
{
	int		j;
	int		len;
	char	var_name[256];
	char	*env_value;

	j = *i;
	len = 0;
	while (input[j] && input[j] != '"')
	{
		if (input[j] == '$' && input[j + 1])
		{
			j = get_env_var_name(input, j, var_name);
			env_value = getenv(var_name);
			if (env_value)
			{
				ft_strlcpy(result + len, env_value, ft_strlen(env_value) + 1);
				len += ft_strlen(env_value);
			}
			j--;
		}
		else
		{
			result[len] = input[j];
			len++;
		}
		j++;
	}
	result[len] = '\0';
	*i = j;
}

/*
Fonction pour traiter les quotes doubles.
1. Sauvegarde la position actuelle (qui est dans la quote d'ouverture).
2. Calcule la longueur de la chaîne entre quotes.
3. Alloue la mémoire nécessaire pour stocker le contenu.
4. Remplit le contenu entre quotes.
5. Retourne le résultat.
*/

static char	*handle_double_quoted(char *input, int *i)
{
	char	*result;
	int		j;
	int		len;

	j = *i;
	len = cal_quoted_len(input, j);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	fill_quoted_content(input, result, &j);
	return (result);
}

/*
Fonction pour traiter les quotes doubles.
1. Appelle la fonction pour traiter les quotes doubles.
2. Retourne le résultat.
*/

char	*expand_var_in_dquotes(char *str)
{
	char	*result;
	int		i;

	i = 0;
	result = handle_double_quoted(str, &i);
	return (result);
}
