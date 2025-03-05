/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:02:26 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 15:23:48 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '$'
		|| c == '>' || c == '<' || c == '\'' || c == '\"');
}

/*
Fonction pour traiter les commandes/arguments.
1. Sauvegarde la position actuelle.
2. Copie le contenu de la commande dans une variable temporaire.
3. Ajoute le token à la liste chainée.
4. Passe les espaces.
*/

void	token_is_command(char *input, int *i, t_token_list *tokens,
		int *is_first_word)
{
	char	temp[256];
	int		j;

	j = 0;
	while (input[*i] && !is_special_char(input[*i]))
	{
		temp[j++] = input[*i];
		(*i)++;
	}
	temp[j] = '\0';
	if (j > 0)
	{
		if (*is_first_word)
		{
			add_token(tokens, temp, COMMAND);
			*is_first_word = 0;
		}
		else if (temp[0] == '-')
			add_token(tokens, temp, ARGUMENT);
		else
			add_token(tokens, temp, STRING);
	}
}

/*
Fonction pour traiter les variables d'environnement.
1. Avance jusqu'au prochain caractère après le '$'.
2. Récupère le nom de la variable d'environnement.
3. Ajoute le token à la liste chainée.
*/

void	assign_env_var(char *input, int *i, t_token_list *tokens)
{
	char	var_name[256];
	int		j;

	j = 0;
	(*i)++;
	if (input[*i] == '?')
	{
		add_token(tokens, "?", EXIT_STATUS);
		(*i)++;
		return ;
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		var_name[j++] = input[*i];
		(*i)++;
	}
	var_name[j] = '\0';
	if (j > 0)
		add_token(tokens, var_name, ENV_VAR);
}
