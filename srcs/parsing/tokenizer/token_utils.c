/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:57:49 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 13:05:21 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction qui cree un nouveau token.
Puisque chaque element (commande, argument, operateurs etc) est un token,
on doit creer un nouveau token a chaque fois qu'on rencontre un nouvel element.
===============================================================================
On alloue la memoire necessaire pour le token.
On va copier la valeur de l'element dans le token.
On va assigner le type de l'element dans le token.
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
t_token		**head = pointeur de la tete de la liste chainee.
t_token		**cur = pointeur de la fin de la liste chainee.
char		*input = valeur de l'element.
t_token_type	type = type de l'element.
=============================================================
Fonction qui ajoute un token a la liste chainee.
On va creer un nouveau token.
Si la liste chainee est vide,
	on va assigner le nouveau token a la tete de la liste.
Sinon, on va assigner le nouveau token a la fin de la liste.
*/

t_token	*add_token(t_token_list *tokens, char *input,
		t_token_type type)
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
Function to skip white spaces between tokens
*/

void	skip_spaces(char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t' || input[*i] == '\n')
		(*i)++;
}

void	free_tokens(t_token_list *tokens_list)
{
	t_token	*tmp;
	t_token *tokens;

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
	return ("UNKNOWN");
}