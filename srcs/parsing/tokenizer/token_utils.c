/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:57:49 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 14:47:14 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
__Fonctionnement :__

Crée un nouveau token pour chaque élément (commande, argument, opérateur, etc.).

1. Alloue un nouveau token (t_token).
2. Copie l'entrée input dans un champ input à l'aide de ft_strdup.
3. Initialise son type (type).
4. Libère la mémoire allouée et retourne NULL si l'allocation du token ou la duplication de input échoue.
5. Initialise le pointeur next à NULL.
6. Retourne le nouveau token.
*/

t_token	*new_token(char *input, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->input = ft_strdup(input);
	if (token->input == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

/*
__Fonctionnement :__

Ajoute un token à la liste chaînée.

t_token     **head = pointeur de la tête de la liste chaînée.
t_token     **cur = pointeur de la fin de la liste chaînée.
char        *input = valeur de l'élément.
t_token_type    type = type de l'élément.

1. Crée un nouveau token avec la valeur input et le type type.
2. L'ajoute à une liste chaînée de tokens (t_token_list).
3. Initialise head et cur avec le nouveau token si la liste est vide.
4. Sinon, l'ajoute à la fin de la liste et met à jour cur.
5. Retourne le token ajouté ou NULL en cas d’échec d’allocation.
*/

t_token	*add_token(t_token_list *tokens, char *input, t_token_type type)
{
	t_token	*new;

	new = new_token(input, type);
	if (!new)
		return (NULL);
	if (!tokens->head)
	{
		tokens->head = new;
		tokens->cur = new;
	}
	else
	{
		tokens->cur->next = new;
		tokens->cur = new;
	}
	return (new);
}

/*
__Fonctionnement :__

Ignore les WHITE SPACE pour positionner i directement sur le premier caractère significatif de l'entrée.

1. Avance l'index i tant que le caractère courant dans input est un SPACE, TAB ou \n.
*/

void	skip_spaces(char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t' || input[*i] == '\n')
		(*i)++;
}

void	free_tokens(t_token_list *tokens_list)
{
	t_token	*tmp;
	t_token	*tokens;

	if (!tokens_list)
		return ;
	tokens = tokens_list->head;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->input);
		free(tmp);
	}
	free(tokens_list);
}

/*
__Fonctionnement :__

Renvoie une chaîne de caractères correspondant au type de token (t_token_type) passé en paramètre.

1. Utilise une série de comparaisons pour associer chaque type à son nom sous forme de chaîne.
2. Retourne UNKNOWN si le type ne correspond à aucun cas connu.
*/

char	*get_token_type_str(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == REDIR_INPUT)
		return ("REDIR_INPUT");
	else if (type == REDIR_OUTPUT)
		return ("REDIR_OUTPUT");
	else if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == EXIT_STATUS)
		return ("EXIT_STATUS");
	else if (type == ENV_VAR)
		return ("ENV_VAR");
	else if (type == REDIR_FILE)
		return ("REDIR_FILE");
	else if (type == STRING)
		return ("STRING");
	else if (type == DOLLAR)
		return ("DOLLAR");
	return ("UNKNOWN");
}
