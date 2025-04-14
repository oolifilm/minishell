/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:45:07 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/14 20:01:46 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		g_exit_status;

char	*expand_token(t_token *token)
{
	char	*value;

	if (token->type == EXIT)
		return (ft_itoa(g_exit_status));
	else if (token->type == ENV)
	{
		value = getenv(token->input);
		printf("[EXPAND] ENV %s = %s\n", token->input,
			value ? value : "(null)");
		if (value)
			return (ft_strdup(value));
		else
			return (ft_strdup(""));
	}
	else
		return (ft_strdup(token->input));
}

void	expand_token_list(t_token *token)
{
	t_token *cur;

	cur = token;
	while (cur)
	{
		if (cur->type == ENV || cur->type == EXIT)
		{
			char *expanded;
			expanded = expand_token(cur);
			free(cur->input);
			cur->input = expanded;
			cur->type = STRING;
		}
		cur = cur->next;
	}
}
