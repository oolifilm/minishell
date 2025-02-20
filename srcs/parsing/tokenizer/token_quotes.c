/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/02/19 10:36:34 by julien           ###   ########.fr       */
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

static void handle_single_quote(char *input, int *i, t_token **head, t_token **cur)
{
    char *content;
    int start;

    start = *i;
    while(input[*i] && input[*i] != '\'')
        (*i)++;
    if (input[*i] == '\'')
    {
        content = ft_substr(input, start, (*i) - start);
        if (content)
        {
            add_token(head, cur, content, STRING);
            free(content);
        }
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

static void handle_double_quotes(char *input, int *i, t_token **head, t_token **cur)
{
    char *content;
    char *expanded;
    int start;

    start = *i;
    while (input[*i] && input[*i] != '"')
        (*i)++;
    if (input[*i] == '"')
    {
        content = ft_substr(input, start - 1, *i - (start - 1));
        if (content)
        {
            expanded = expand_var_in_dquotes(content);
            if (expanded)
            {
                add_token(head, cur, expanded, STRING);
                free(expanded);
            }
            free(content);
        }
    }
}

/*
Fonction qui va assigner le type de quote rencontré.
1. Crée un tableau temporaire avec la quote et le caractère nul.
2. Si c'est un simple quote ('), ajoute un token SINGLE_QUOTE.
3. Si c'est un double quote ("), ajoute un token DOUBLE_QUOTE.
4. Le token contient uniquement le caractère de la quote.
*/

void	assign_quote(char input, t_token **head, t_token **cur)
{
	char	temp[2] = {input, '\0'};

	if (input == '\'')
		add_token(head, cur, temp, SINGLE_QUOTE);
	else if (input == '\"')
		add_token(head, cur, temp, DOUBLE_QUOTE);
}

/*
Fonction qui va gérer le contenu entre quotes.
1. Avance d'une position pour sauter la quote d'ouverture.
2. Si c'est un double quote ("), appelle handle_double_quotes pour l'expansion.
3. Si c'est une simple quote ('), appelle handle_single_quote pour garder tel quel.
4. Le traitement spécifique est délégué à la fonction appropriée.
*/

void handle_quoted_content(char *input, int *i, t_token **head, t_token **cur, char quote_type)
{
    (*i)++;
    if (quote_type == '"')
        handle_double_quotes(input, i, head, cur);
    else
        handle_single_quote(input, i, head, cur);
}


