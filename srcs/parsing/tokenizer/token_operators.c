/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:25 by julien            #+#    #+#             */
/*   Updated: 2025/04/11 17:53:31 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Gère le caractère |. */

void	assign_pipe(char input, t_token_list *tokens)
{
	if (input == '|')
		add_token(tokens, "|", PIPE);
}

/* Gère le caractère $. */

void	assign_dollar(char *input, int *i, t_token_list *tokens)
{
	char var_name[256];
	int j;

	(*i)++;
	if (input[*i] == '?')
	{
		add_token(tokens, "?", EXIT);
		(*i)++;
		return;
	}
	j = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_') && j < 255)
	{
		var_name[j] = input[*i];
		j++;
		(*i)++;
	}
	var_name[j] = '\0';
	if (j > 0)
		add_token(tokens, var_name, ENV);
}

/* Extrait le nom d'une variable d'environnement à partir d'une chaîne input. */

int	get_env_var_name(char *input, int j, char *var_name)
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
