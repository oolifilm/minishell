/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/02/28 23:13:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

