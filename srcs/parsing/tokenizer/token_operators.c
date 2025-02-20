/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/02/19 12:31:19 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Note sur le pointeur i :
1. Utilisation d'un pointeur pour modifier i directement dans la fonction
2. Évite de retourner la nouvelle valeur de i
3. Simplifie la gestion des positions dans le parsing
==Fonction qui va assigner les opérateurs de redirection==
1. Détecte la présence d'un opérateur de redirection (< ou >)
2. Crée un token pour l'opérateur simple s'il est trouvé
3. Vérifie si l'opérateur est double (<< ou >>)
4. Crée un token spécifique pour l'opérateur double
*/

void	assign_redirection(char *input, int *i, t_token **head, t_token **cur)
{
	char	temp[3] = {0};

	if (input[*i] == '>' || input[*i] == '<')
	{
		if (input[*i + 1] == input[*i])
		{
			temp[0] = input[*i];
			temp[1] = input[*i + 1];
			add_token(head, cur, temp, DOUBLE_REDIRECTION);
			(*i)++;
		}
		else
		{
			temp[0] = input[*i];
			add_token(head, cur, temp, REDIRECTION);
			(*i)++;
		}
	}
}

void	assign_pipe(char input, t_token **head, t_token **cur)
{
	if (input == '|')
		add_token(head, cur, "|", PIPE);
}

void	assign_dollar(char input, t_token **head, t_token **cur)
{
	if (input == '$')
		add_token(head, cur, "$", DOLLAR);
}

