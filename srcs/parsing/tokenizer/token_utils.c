/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:57:49 by julien            #+#    #+#             */
/*   Updated: 2025/02/20 12:36:16 by jbanchon         ###   ########.fr       */
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

int global_token_count = 0;

t_token	*new_token(char *input, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	global_token_count++;
	printf(GREEN "[ALLOC] Token created: %s (Total: %d)\n" RESET, input, global_token_count);
	printf("Memory allocated for new token\n");
	token->input = ft_strdup(input);
	printf("Memory allocatec for input with ft_strdup\n");
	if (token->input == NULL)
	{
		free(token);
		global_token_count--;
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	printf("New token created: %s\n", input); 
	return (token);
}

/*
t_token			**head = pointeur de la tete de la liste chainee.
t_token			**cur = pointeur de la fin de la liste chainee.
char			*input = valeur de l'element.
t_token_type	type = type de l'element.
==================================================================================================
Fonction qui ajoute un token a la liste chainee.
On va creer un nouveau token.
Si la liste chainee est vide,
	on va assigner le nouveau token a la tete de la liste.
Sinon, on va assigner le nouveau token a la fin de la liste.
*/

t_token	*add_token(t_token **head, t_token **cur, char *input,
		t_token_type type)
{
	t_token	*new;

	new = new_token(input, type);
	if (!new)
		return (NULL);
	if (!*head)
	{
		*head = new;
		*cur = new;
	}
	else
	{
		(*cur)->next = new;
		*cur = new;
	}
	printf("Token added: %s\n", input);
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


void free_tokens(t_token *tokens)
{
    t_token *tmp;
    
    if (!tokens)
    {
        printf(RED "[FREE] No tokens to free.\n" RESET);
        return;
    }
    while (tokens)
    {
		tmp = tokens;
		printf("[FREE] Freeing token: %s\n", tokens->input);
        tokens = tokens->next;
        free(tmp->input);
        free(tmp);
		global_token_count--;
		printf(RED "[FREE] Token freed (Remaining: %d)\n" RESET, global_token_count);
    }
}
