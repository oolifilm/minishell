/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:02:26 by julien            #+#    #+#             */
/*   Updated: 2025/04/14 20:03:46 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Détermine si un caractère est un caractère 
spécial dans l'analyse de la commande. */

static bool	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '$'
		|| c == '>' || c == '<' || c == '\'' || c == '\"');
}

/* Extrait un mot de l'entrée `input` et le 
classe en fonction de son rôle dans la commande. */

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

/* Extrait une variable d'environnement à partir 
de l'entrée input lorsqu'un $ est rencontré. */

void	assign_env_var(char *input, int *i, t_token_list *tokens)
{
	char	var_name[256];
	int		j;

	j = 0;
	(*i)++;
	if (input[*i] == '?')
	{
		add_token(tokens, "?", EXIT, 0);
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
		add_token(tokens, var_name, ENV, 0);
}
