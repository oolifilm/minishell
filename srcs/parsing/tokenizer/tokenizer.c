/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/11 13:14:18 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Initialise une nouvelle liste chaînée de tokens (t_token_list).

1. Alloue dynamiquement une structure t_token_list.
2. Vérifie si l'allocation a échoué et retourne NULL en cas d'échec.
3. Initialise les pointeurs :
   - head à NULL (début de la liste vide).
   - cur à NULL (aucun token actuel).
4. Retourne le pointeur vers la liste nouvellement créée.
*/

t_token_list	*init_token_list(void)
{
	t_token_list	*tokens;

	tokens = (t_token_list *)malloc(sizeof(t_token_list));
	if (!tokens)
		return (NULL);
	tokens->head = NULL;
	tokens->cur = NULL;
	return (tokens);
}

/*
__Fonctionnement :__

Analyse la chaîne de caractères input et la transforme en une liste chaînée de tokens (t_token_list).

1. Ignore les espaces initiaux.
2. Parcourt l'entrée caractère par caractère pour identifier et traiter les différents types de tokens :
   - Variables : $
   - Pipes : |
   - Redirections : < ou >
   - Contenu entre guillemets : " " ou ' '
3. Détecte les commandes et gère leur position dans la ligne de commande (is_first_word).
4. Utilise init_token_list() pour initialiser la liste des tokens.
5. Retourne la liste chaînée contenant les tokens extraits.
*/

t_token_list	*tokenize_input(char *input)
{
	int				i;
	t_token_list	*tokens;
	int				is_first_word;
	size_t			len;

	len = ft_strlen(input);
	i = 0;
	is_first_word = 1;
	if (has_unclosed_quote(input))
	{
		printf("[ERROR] Syntax error near ' '\n");
		return (NULL); // Retourne NULL ou gère l'erreur selon ton besoin
	}
	tokens = init_token_list();
	skip_spaces(input, &i);
	while (i < (int)len)
	{
		assign_dollar(input[i], tokens);
		assign_pipe(input[i], tokens);
		assign_redirection(input, &i, tokens);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, tokens, input[i]);
		else
		{
			token_is_command(input, &i, tokens, &is_first_word);
			i++;
		}
	}
	return (tokens);
}
