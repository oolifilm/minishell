/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/11 15:57:28 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Fonction qui cree un nouveau token.
Puisque chaque element (commande, argument, operateurs etc) est un token,
on doit creer un nouveau token a chaque fois qu'on rencontre un nouvel element.
===============================================================================
On alloue la memoire necessaire pour le token.
On va copier la valeur de l'element dans le token.
On va assigner le type de l'element dans le token.
*/

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*add_token(t_token **head, t_token **current, char *value,
		t_token_type type)
{
	t_token	*new;

	new = new_token(value, type);
	if (!new)
		return (NULL);
	if (!*head)
	{
		*head = new;
		*current = new;
	}
	else
	{
		(*current)->next = new;
		*current = new;
	}
	return (new);
}

t_token	*assign_quote(char *input)
{
	int		i;
	t_token	*head;
	t_token	*current;
	char	temp[2] = {0};

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			add_token(&head, &current, temp, SINGLE_QUOTE);
		if (input[i] == '\"')
			add_token(&head, &current, temp, DOUBLE_QUOTE);
		i++;
	}
	return (head);
}

t_token	*assign_redirection(char *input)
{
	int		i;
	t_token	*head;
	t_token	*current;
	char	temp[2] = {0};

	i = 0;
	head = NULL;
	current = NULL;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (input[i + 1] == input[i])
			{
				temp[0] = input[i];
				temp[1] = input[i + 1];
				add_token(&head, &current, temp, DOUBLE_REDIRECTION);
				i++;
			}
			else
			{
				temp[0] = input[i];
				add_token(&head, &current, temp, REDIRECTION);
			}
		}
		i++;
	}
	return (head);
}

t_token	*assign_pipe(char *input)
{
	int		i;
	char	temp[2] = {0};
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	current = NULL;
	while (input[i])
	{
		if (input[i] == '|')
		{
			temp[0] = input[i];
			add_token(&head, &current, temp, PIPE);
		}
		i++;
	}
	return (head);
}

t_token	*assign_dollar(char *input)
{
	int		i;
	char	temp[2] = {0};
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	current = NULL;
	while (input[i])
	{
		if (input[i] == '$')
		{
			temp[0] = input[i];
			add_token(&head, &current, temp, DOLAR);
		}
		i++;
	}
	return (head);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*temp;

	head = NULL;
	current = NULL;
	temp = assign_quote(input);
	while (temp)
	{
		add_token(&head, &current, temp->value, temp->type);
		temp = temp->next;
	}
	temp = assign_redirection(input);
	while (temp)
	{
		add_token(&head, &current, temp->value, temp->type);
		temp = temp->next;
	}
	temp = assign_pipe(input);
	while (temp)
	{
		add_token(&head, &current, temp->value, temp->type);
		temp = temp->next;
	}
	temp = assign_dollar(input);
	while (temp)
	{
		add_token(&head, &current, temp->value, temp->type);
		temp = temp->next;
	}
	temp = token_is_command(input);
	while (temp)
	{
		add_token(&head, &current, temp->value, temp->type);
		temp = temp->next;
	}
	return (head);
}

t_token	*token_is_command(char *input)
{
	t_token	*current;
	int		i;
	int		j;
	char	temp[256];
	t_token	*head;
	int		is_command;

	i = 0;
	j = 0;
	is_command = 1;
	head = NULL;
	current = NULL;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			temp[j++] = input[i];
		else if (j > 0)
		{
			temp[j] = '\0';
			if (is_command)
			{
				add_token(&head, &current, temp, COMMAND);
				is_command = 0;
			}
            else
                add_token(&head, &current, temp, ARGUMENT);
            j = 0;
		}
		i++;
	}
	if (j > 0)
	{
		temp[j] = '\0';
        if (is_command)
            add_token(&head, &current, temp, COMMAND);
        else
            add_token(&head, &current, temp, ARGUMENT);
	}
	return (head);
}
