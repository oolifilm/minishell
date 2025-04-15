/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/04/15 16:05:43 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_invalid_first_token(t_token *head)
{
	if (!head)
		return (printf("[ERROR] Token list is NULL.\n"), 1);
	if (head->type == PIPE)
	{
		printf("[ERROR] Pipe can't be the first argument.\n");
		return (1);
	}
	return (0);
}

int	handle_pipes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == STRING)
		{
			if (!tokens->quoted && ft_strchr(tokens->input, '|'))
			{
				printf("[ERROR] Pipe found in unquoted string.\n");
				return (1);
			}
		}
		if (tokens->type == PIPE)
		{
			if (!tokens->next)
			{
				printf("[ERROR] Pipe must be followed by a command.\n");
				return (1);
			}
			else if (tokens->next->type == PIPE)
			{
				printf("[ERROR] Found consecutive pipes.\n");
				return (1);
			}
			if (tokens->next->type == CMD)
			{
				if (!is_builtin(tokens->next->input)) //pb pour autre que builtin ex : cat -e
				{
					printf("[ERROR] Following command is not valid.\n");
					return (1);
				}
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	has_invalid_redirection(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next)
			{
				printf("[ERROR] Redirection must be followed by a target.\n");
				return (1);
			}
			if (tokens->next->type == REDIR_IN
				|| tokens->next->type == REDIR_OUT
				|| tokens->next->type == APPEND
				|| tokens->next->type == HEREDOC)
			{
				printf("[ERROR] Invalid redirection: cannot chain redirection symbols.\n");
				return (1);
			}
			if (tokens->next->type != REDIR_FILE && tokens->next->type != STRING
				&& tokens->next->type != ENV)
			{
				printf("[ERROR] Unexpected token after redirection.\n");
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	has_unclosed_quote(char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quote = !single_quote;
		if (*input == '"')
			double_quote = !double_quote;
		input++;
	}
	if (single_quote || double_quote)
	{
		return (1);
	}
	return (0);
}

int	parse_tokens(t_token_list *tokens)
{
	if (!tokens || !tokens->head)
		return (1);
	if (is_invalid_first_token(tokens->head))
		return (0);
	if (handle_pipes(tokens->head))
		return (0);
	if (has_invalid_redirection(tokens->head))
		return (0);
	return (1);
}
