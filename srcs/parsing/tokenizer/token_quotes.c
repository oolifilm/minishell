/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 16:20:51 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Extrait le contenu entre apostrophes (' ') dans l'entrée input.

1. Ignore l'apostrophe d'ouverture, enregistre la position de départ.
2. Avance jusqu'à l'apostrophe de fermeture.
3. Extrait le contenu avec ft_substr si l'apostrophe de fermeture est trouvée.
4. L'ajoute à la liste des tokens en tant que STRING.
5. Libère la mémoire allouée.
6. Met à jour l'index i pour poursuivre l'analyse.
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
__Fonctionnement :__

Extrait le contenu entre guillemets (" ) dans l'entrée input.

1. Ignore le guillemet d'ouverture, enregistre la position de départ.
2. Avance jusqu'au guillemet de fermeture.
3. Extrait le contenu avec ft_substr si l'apostrophe de fermeture est trouvée.
4. Effectue une expansion des variables avec expand_var_in_dquotes.
4. L'ajoute à la liste des tokens en tant que STRING.
5. Libère la mémoire allouée.
6. Met à jour l'index i pour poursuivre l'analyse.
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
__Fonctionnement :__

Gère le contenu entre guillemets et apostrophes dans l'entrée input.

1. Vérifie le type de citation.
2. Appelle la fonction handle_double_quotes pour " ", qui permet l'expansion de variables.
3. Appelle la fonction handle_single_quote pour ' ', qui conserve le texte tel quel.
4. Met à jour l'index i pour poursuivre l'analyse.
*/

void	handle_quoted_content(char *input, int *i, t_token_list *tokens,
		char quote_type)
{
	if (quote_type == '"')
		handle_double_quotes(input, i, tokens);
	else
		handle_single_quote(input, i, tokens);
}
