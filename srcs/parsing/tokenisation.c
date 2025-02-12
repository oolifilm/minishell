/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/12 15:17:36 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction qui cree un nouveau token.
Puisque chaque element (commande, OPTION, operateurs etc) est un token,
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
		free(input);
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
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
	return (new);
}

/*

Fonction qui va assigner les quotes.
On va verifier si on a une quote.
Si on a une quote, on va creer un nouveau token.
On va verifier si on a une double quote.
Si on a une double quote, on va creer un nouveau token.
*/

void	assign_quote(char input, t_token **head, t_token **cur)
{
	char	temp[2] = {input, '\0'};

	if (input == '\'')
	{
		add_token(head, cur, temp, SINGLE_QUOTE);
	}
	else if (input == '\"')
	{
		add_token(head, cur, temp, DOUBLE_QUOTE);
	}
}

/*
Pointeur de i pour manipuler la variable i dans la fonction.
On evite de renvoyer des valeurs pour i,
	sinon on devrait renvoyer i a chaque fois qu'on modifie i.
==================================================================================================
Fonction qui va assigner les operateurs de redirection.
On va verifier si on a un operateur de redirection.
Si on a un operateur de redirection, on va creer un nouveau token.
On va verifier si on a un double operateur de redirection.
Si on a un double operateur de redirection, on va creer un nouveau token.
*/

void	assign_redirection(char *input, int *i, t_token **head, t_token **cur)
{
	char	temp[3] = {0};

	if (input[*i] == '>' || input[*i] == '<')
	{
		if (input[*i + 1] == input[*i])
		{
			temp[0] = input[*i];
			temp[1] = input[*i + 1];
			add_token(head, cur, temp, DOUBLE_REDIRECTION);
			(*i)++;
		}
		else
		{
			temp[0] = input[*i];
			add_token(head, cur, temp, REDIRECTION);
		}
		(*i)++;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (input[*i] && input[*i] != '>' && input[*i] != '<'
			&& input[*i] != '|')
			token_is_outfile(input, i, head, cur);
	}
}

void	token_is_outfile(char *input, int *i, t_token **head, t_token **cur)
{
	char	temp[256];
	int		j;

	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\n' && input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		temp[j++] = input[*i];
		(*i)++;
	}
	temp[j] = '\0';
	if (j > 0)
		add_token(head, cur, temp, OUTFILE);
}

void	assign_pipe(char input, t_token **head, t_token **cur)
{
	if (input == '|')
	{
		add_token(head, cur, "|", PIPE);
	}
}

void	assign_dollar(char input, t_token **head, t_token **cur)
{
	if (input == '$')
	{
		add_token(head, cur, "$", DOLLAR);
	}
}

t_token	*tokenize_input(char *input)
{
	int				i;
	int				is_first;
	t_token			*head;
	t_token			*cur;
	t_token_info	info = {&head, &cur, &is_first};

	i = 0;
	is_first = 1;
	head = NULL;
	cur = NULL;
	// info.head = &head;
	// info.cur = &cur;
	// info.is_first = &is_first;
	while (input[i])
	{
		assign_dollar(input[i], &head, &cur);
		assign_pipe(input[i], &head, &cur);
		assign_redirection(input, &i, &head, &cur);
		assign_quote(input[i], &head, &cur);
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			token_is_command(input, &i, &info);
		i++;
	}
	return (head);
}

void	token_is_command(char *input, int *i, t_token_info *info)
{
	char	temp[256];
	int		j;

	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\n' && input[*i] != '|' && input[*i] != '$'
		&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		temp[j++] = input[*i];
		(*i)++;
	}
	temp[j] = '\0';
	if (j > 0)
	{
		if (*(info->is_first))
		{
			add_token(info->head, info->cur, temp, COMMAND);
			*(info->is_first) = 0;
		}
		else if (temp[0] == '-')
			add_token(info->head, info->cur, temp, OPTION);
		else
			add_token(info->head, info->cur, temp, ARGUMENT);
	}
}
