/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:09:13 by julien            #+#    #+#             */
/*   Updated: 2025/04/10 16:24:35 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	get_redir_file(char *input, int *i, t_token_list *tokens)
{
	int		start;
	char	*file;

	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '|')
		(*i)++;
	if (*i > start)
	{
		file = ft_substr(input, start, *i - start);
		if (file)
		{
			add_token(tokens, file, TARGET);
			free(file);
		}
	}
}

static void	handle_output_redir(char *input, int *i, t_token_list *tokens)
{
	char	temp[3];

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	if (input[*i + 1] == '>' && input[*i + 2] == '>')
	{
		printf("[ERROR] Redirection must be followed by a valid target.\n");
		*i = ft_strlen(input);
		return ;
	}
	if (input[*i + 1] == '>')
	{
		temp[0] = input[*i];
		temp[1] = input[*i + 1];
		add_token(tokens, temp, APPEND);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_OUT);
	}
	get_redir_file(input, i, tokens);
}

/*
__Fonctionnement :__

Gère les redirections d'entrée (< et <<).

1. Détecte d'abord une erreur de syntaxe lorsque trois < consécutifs apparaissent.
2. Affiche un message avant d'arrêter le parsing dans ce cas.
3. Différencie les cas << et <.
4. Ajoute un token HEREDOC pour << ou REDIR_IN pour <.
5. Appelle get_redir_file pour récupérer le fichier cible de la redirection.
*/

static void	handle_input_redir(char *input, int *i, t_token_list *tokens)
{
	char	temp[3];

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	if (input[*i + 1] == '<' && input[*i + 2] == '<')
	{
		printf("[ERROR] Redirection must be followed by a valid target.\n");
		*i = ft_strlen(input);
		return ;
	}
	if (input[*i + 1] == '<')
	{
		temp[0] = input[*i];
		temp[1] = input[*i + 1];
		add_token(tokens, temp, HEREDOC);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_IN);
	}
	get_redir_file(input, i, tokens);
}

/*
__Fonctionnement :__

Détecte si le caractère actuel dans input est un symbole de redirection.

1. Appelle handle_output_redir si c'est > pour gérer la redirection de sortie.
2. Appelle handle_input_redir si c'est < pour gérer la redirection d'entrée.
*/

void	assign_redirection(char *input, int *i, t_token_list *tokens)
{
	if (input[*i] == '>')
		handle_output_redir(input, i, tokens);
	else if (input[*i] == '<')
		handle_input_redir(input, i, tokens);
}
