/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:02:26 by julien            #+#    #+#             */
/*   Updated: 2025/04/15 18:45:33 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Détermine si un caractère est un 
caractère spécial dans l'analyse de la commande.

1. Considère comme spécial : SPACE, TAB, \n, |, >, <, " ", ' ' et $
2. Retourne true si le caractère est spécial, false sinon.
*/

static bool	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '$'
		|| c == '>' || c == '<' || c == '\'' || c == '\"');
}

/*
__Fonctionnement :__

Extrait un mot de l'entrée `input` et le classe en fonction de son rôle dans la commande.

1. Parcourt les caractères jusqu'à rencontrer 
un caractère spécial (défini par is_special_char).
2. L'ajoute comme COMMAND si le mot est 
le premier dans la ligne (is_first_word est vrai).
3. Réinitialise is_first_word si un PIPE est rencontré avant.
4. L'ajoute comme ARGUMENT s'il n'est pas 
le premier mot et qu'il commence par un tiret (-).
5. L'ajoute comme STRING s'il n'est pas 
le premier mot et qu'il ne commence pas par un tiret (-).
6. Met à jour l'index i et ajoute le token à la liste.
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
		if (tokens->cur && tokens->cur->type == PIPE)
			*is_first_word = 1;
		if (*is_first_word)
		{
			add_token(tokens, temp, CMD, 0);
			*is_first_word = 0;
		}
		else if (temp[0] == '-')
			add_token(tokens, temp, ARG, 0);
		else
			add_token(tokens, temp, STRING, 0);
	}
}

/*
__Fonctionnement :__

Extrait une variable d'environnement à 
partir de l'entrée input lorsqu'un $ est rencontré.

1. Ignore le $ initial et vérifie 
si le caractère suivant est ?.
2. Ajoute un token EXIT_STATUS si c'est le cas.
3. Récupère le nom de la variable 
(composé de caractères alphanumériques ou _ sinon.
4. L'ajoute à la liste des tokens en tant que ENV_VAR.
5. Met à jour l'index i pour continuer l'analyse.
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
