/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:02:26 by julien            #+#    #+#             */
/*   Updated: 2025/02/20 12:43:02 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction pour traiter les commandes/arguments.
1. Sauvegarde la position actuelle.
2. Copie le contenu de la commande dans une variable temporaire.
3. Ajoute le token à la liste chainée.
4. Passe les espaces.
*/

void	token_is_command(char *input, int *i, t_token **head, t_token **cur,
		int *is_first_word)
{
	char	temp[256];
	int		j;

	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\n' && input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		temp[j] = input[*i];
		(*i)++;
		j++;
	}
	temp[j] = '\0';
	if (j > 0)
	{
		if (*is_first_word)
		{
			add_token(head, cur, temp, COMMAND);
			*is_first_word = 0;
		}
		else if (temp[0] == '-')
			add_token(head, cur, temp, ARGUMENT);
		else
			add_token(head, cur, temp, STRING);
		skip_spaces(input, i);
	}
}

/*
Fonction pour traiter les variables d'environnement.
1. Avance jusqu'au prochain caractère après le '$'.
2. Récupère le nom de la variable d'environnement.
3. Ajoute le token à la liste chainée.
*/

void	assign_env_var(char *input, int *i, t_token **head, t_token **cur)
{
	char	var_name[256];
	int		j;

	j = 0;
	(*i)++;
	if (input[*i] == '?')
	{
		add_token(head, cur, "?", EXIT_STATUS);
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
		add_token(head, cur, var_name, ENV_VAR);
}
