/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/04/14 20:07:33 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Extrait le contenu entre apostrophes (' ') dans l'entrée input. */

static void	handle_single_quote(char *input, int *i, t_token_list *tokens)
{
	char	buffer[1024];
	int		len;
	int		start;

	len = 0;
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
	{
		while (start < *i && len < 1023)
			buffer[len++] = input[start++];
		(*i)++;
		while (input[*i] && !ft_isspace(input[*i])
			&& !is_token_breaker(input[*i]) && len < 1023)
			buffer[len++] = input[(*i)++];
		buffer[len] = '\0';
		add_token(tokens, ft_strdup(buffer), STRING, 1);
	}
}

/* Extrait le contenu entre guillemets (" ) dans l'entrée input. */

static void	handle_double_quotes(char *input, int *i, t_token_list *tokens)
{
	char	buffer[1024];
	int		len;
	int		start;
	char	*content;
	char	*expanded;

	len = 0;
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
			free(content);
			if (expanded)
			{
				ft_strlcpy(buffer, expanded, sizeof(buffer));
				len = ft_strlen(buffer);
				free(expanded);
				(*i)++;
				while (input[*i] && !ft_isspace(input[*i])
					&& !is_token_breaker(input[*i]))
					buffer[len++] = input[(*i)++];
				buffer[len] = '\0';
				add_token(tokens, ft_strdup(buffer), STRING, 1);
			}
		}
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
