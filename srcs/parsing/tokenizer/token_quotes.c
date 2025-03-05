/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 15:08:10 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction qui va traiter les quotes simples.
1. Sauvegarde la position actuelle (qui est dans la quote d'ouverture).
2. Avance jusqu'à la quote fermante.
3. Extrait tout le contenu entre quotes.
4. Ajoute le résultat comme token de type STRING.
*/

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

/*
Fonction qui va traiter les quotes doubles.
1. Sauvegarde la position actuelle (qui est dans la quote d'ouverture).
2. Avance jusqu'à la quote fermante.
3. Extrait tout le contenu entre quotes.
4. Expande les variables d'environnement dans le contenu extrait.
5. Ajoute le résultat comme token de type STRING.
*/

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

/*
Fonction qui gère le contenu entre quotes (simples ou doubles).
1. Calcule la position de départ juste après la quote d'ouverture
2. Cherche la quote de fermeture correspondante
3. Extrait le contenu entre les quotes
4. Pour les doubles quotes ("), expande les variables d'environnement
5. Pour les simples quotes ('), garde le contenu tel quel
6. Ajoute le résultat comme token de type STRING
*/

void	handle_quoted_content(char *input, int *i, t_token_list *tokens,
		char quote_type)
{
	if (quote_type == '"')
		handle_double_quotes(input, i, tokens);
	else
		handle_single_quote(input, i, tokens);
}
