/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:39:41 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 16:22:57 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Extrait le nom d'une variable d'environnement à partir d'une chaîne input.

1. Commence à partir de l'index j.
2. Copie les caractères alphanumériques et les underscores dans var_name.
3. S'arrête dès qu'un caractère non valide est rencontré. 
4. Retourne le nouvel index j après la variable.
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
__Fonctionnement :__

Calcule la longueur d'une chaîne entre guillemets.

1. Parcourt input à partir de j jusqu'au guillement de fermeture.
2. Extrait le nom de la variable avec get_env_var_name si rencontre d'un $.
3. Récupère la valeur de cette variable via getenv(var_name).
4. Ajoute sa longueur à len si elle existe.
5. Compte simplement les caractères normaux sinon.
6. Retourne la longueur totale après expansion des variables.
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
__Fontionnement :__

Remplit result avec le contenu de input.

1. Parcourt innput depuis *i jusu'au guillement de fermeture.
2. Remplit result avec le meme processus que cal_quoted_len.
3. Extrait le nom de la variable avec get_env_var_name si rencontre d'un $.
4. Cherche sa valeur avec getenv(var_name).
5. Copie la valeur dans result avec ft_strcpy si la variable existe.
6. Copie le caractère directement si ce n'est pas une variable.
7. Met *i à jour pour pointer après la fin du contenu cité.
*/

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
			result[len++] = input[j];
		j++;
	}
	result[len] = '\0';
	*i = j;
}

/*
__Fonctionnement :__

Extrait et traite le contenu d'une chaîne entre guillemets.

1. Détermine la longueur de la chaîne après expansion des variables avec cal_quoted_len.
2. Alloue juste l'espace nécessaire pour result.
3. Utilise malloc(len+1) pour stocker la chaîne expandée.
4. Vérifie l’échec de l’allocation.
5. Remplit result en traitant l'expansion des variables d'environnement avec fill_quoted_content.
6. Renvoie result avec son contenu traité.
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
__Fonctionnement :__

Wrappe handle_double_quoted.

1. L'appelle.
2. Retourne result.
*/

char	*expand_var_in_dquotes(char *str)
{
	char	*result;
	int		i;

	i = 0;
	result = handle_double_quoted(str, &i);
	return (result);
}
