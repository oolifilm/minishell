/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:09:13 by julien            #+#    #+#             */
/*   Updated: 2025/04/14 20:04:01 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Extrait le nom d’un fichier après un opérateur de redirection (>>, <<). */

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
			add_token(tokens, file, REDIR_FILE, 0);
			free(file);
		}
	}
}

/* Gère les redirections de sortie (> et >>). */

static void	handle_output_redir(char *input, int *i, t_token_list *tokens)
{
	char	temp[3];

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	if (input[*i + 1] && input[*i + 2] && input[*i + 1] == '>' && input[*i
			+ 2] == '>')
	{
		printf("[ERROR] Redirection must be followed by a valid target.\n");
		*i = ft_strlen(input);
		return ;
	}
	if (input[*i + 1] == '>')
	{
		temp[0] = input[*i];
		temp[1] = input[*i + 1];
		add_token(tokens, temp, APPEND, 0);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_OUT, 0);
	}
	get_redir_file(input, i, tokens);
}

/* Gère les redirections d'entrée (< et <<). */

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
		add_token(tokens, temp, HEREDOC, 0);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_IN, 0);
	}
	get_redir_file(input, i, tokens);
}

/* Détecte si le caractère actuel dans input est un symbole de redirection. */

void	assign_redirection(char *input, int *i, t_token_list *tokens)
{
	if (input[*i] == '>')
		handle_output_redir(input, i, tokens);
	else if (input[*i] == '<')
		handle_input_redir(input, i, tokens);
}
