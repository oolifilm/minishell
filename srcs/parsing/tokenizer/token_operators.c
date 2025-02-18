/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 11:04:27 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Pointeur de i pour manipuler la variable i dans la fonction.
On evite de renvoyer des valeurs pour i,
	sinon on devrait renvoyer i a chaque fois qu'on modifie i.
==================================================================================================
Fonction qui va assigner les operateurs de redirection.
On va verifier si on a un operateur de redirection.
Si on a un operateur de redirection, on va creer un nouveau token.
On va verifier si on a un double operateur de redirection.
Si on a un double operateur de redirection, on va creer un nouveau token.
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
	{
		add_token(head, cur, "|", PIPE);
	}
}

void	assign_dollar(char input, t_token **head, t_token **cur)
{
	if (input == '$')
	{
		add_token(head, cur, "$", DOLLAR);
	}
}

