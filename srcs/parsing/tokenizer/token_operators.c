/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 14:41:53 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	assign_pipe(char input, t_token_list *tokens)
{
	if (input == '|')
		add_token(tokens, "|", PIPE);
}

void	assign_dollar(char input, t_token_list *tokens)
{
	if (input == '$')
		add_token(tokens, "$", DOLLAR);
}
