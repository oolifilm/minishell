/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:57:49 by julien            #+#    #+#             */
/*   Updated: 2025/04/10 16:24:04 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

char	*get_token_type_str(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == EXIT)
		return ("EXIT");
	else if (type == ENV)
		return ("ENV");
	else if (type == TARGET)
		return ("TARGET");
	else if (type == STRING)
		return ("STRING");
	else if (type == DOLLAR)
		return ("DOLLAR");
	return ("UNKNOWN");
}
