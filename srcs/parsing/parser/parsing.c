/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:27:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/03/10 16:55:24 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_invalid_first_token(t_token *head)
{
	if (!head)
		return (printf("[ERROR] No tokens found\n"), 1);
	if (head->type == PIPE || head->type == REDIR_INPUT
		|| head->type == REDIR_OUTPUT || head->type == REDIR_APPEND
		|| head->type == HEREDOC)
	{
		printf("[ERROR] Syntax error near '%s'\n", head->input);
		return (1);
	}
	return (0);
}

int	has_consecutive_pipes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!tokens->next || tokens->next->type == PIPE)
			{
				printf("[ERROR] Syntax error near '|'\n");
				return (1);
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
		if (tokens->type == REDIR_INPUT || tokens->type == REDIR_OUTPUT
			|| tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
		{
			if (!tokens->next || (tokens->next->type != REDIR_FILE
					&& tokens->next->type != STRING
					&& tokens->next->type != ENV_VAR))
			{
				printf("[ERROR] Syntax error near '%s'\n", tokens->input);
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
		return (printf("[ERROR] Empty token list\n"), 0);
	if (is_invalid_first_token(tokens->head))
		return (0);
	if (has_consecutive_pipes(tokens->head))
		return (0);
	if (has_invalid_redirection(tokens->head))
		return (0);
	//	if (has_unclosed_quotes(tokens->head))
	//		return (0);
	return (1);
}
