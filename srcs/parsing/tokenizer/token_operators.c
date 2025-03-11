/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 14:46:06 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Gère le caractère |.

1. Vérifie si le caractère input est un pipe (|).
2. Ajoute un token PIPE à la liste des tokens avec la valeur "|" si c'est le cas.
*/

void	assign_pipe(char input, t_token_list *tokens)
{
	if (input == '|')
		add_token(tokens, "|", PIPE);
}

/*
__Fonctionnement :__

Gère le caractère $.

1. Vérifie si le caractère input est un dollar ($).
2. Ajoute un token DOLLAR à la liste des tokens avec la valeur "$" si c'est le cas.
*/

void	assign_dollar(char input, t_token_list *tokens)
{
	if (input == '$')
		add_token(tokens, "$", DOLLAR);
}
