/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/04/10 18:26:26 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Extrait le contenu entre apostrophes (' ') dans l'entrée input. */

static void	handle_single_quote(char *input, int *i, t_token_list *tokens)
{
	char	*content;
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
	{
		content = ft_substr(input, start, *i - start);
		if (content)
		{
			add_token(tokens, content, STRING);
			free(content);
		}
		(*i)++;
	}
}

/* Extrait le contenu entre guillemets (" ) dans l'entrée input. */

static void	handle_double_quotes(char *input, int *i, t_token_list *tokens)
{
	char	*content;
	char	*expanded;
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
	{
		content = ft_substr(input, start, *i - start);
		if (content)
		{
			expanded = expand_var_in_dquotes(content);
			if (expanded)
			{
				add_token(tokens, expanded, STRING);
				free(expanded);
			}
			free(content);
		}
		(*i)++;
	}
}

/* Gère le contenu entre guillemets et apostrophes dans l'entrée input.*/

void	handle_quoted_content(char *input, int *i, t_token_list *tokens,
		char quote_type)
{
	if (quote_type == '"')
		handle_double_quotes(input, i, tokens);
	else
		handle_single_quote(input, i, tokens);
}
