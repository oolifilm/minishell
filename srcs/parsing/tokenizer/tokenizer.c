/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/15 15:41:45 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_ignored_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == ':' || c == '!'
		|| c == ';' || c == '@');
}

int	is_ignorable_input(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_ignored_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Initialise une nouvelle liste chaînée
de tokens (t_token_list). */

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

/* Analyse la chaîne de caractères input et la
transforme en une liste chaînée de tokens (t_token_list).*/

static int	init_tokenizer(char *input, t_token_list **tokens, int *i)
{
	if (has_unclosed_quote(input))
	{
		printf("[ERROR] Lexer found an unclosed quote.\n");
		return (0);
	}
	*tokens = init_token_list();
	*i = 0;
	skip_spaces(input, i);
	return (1);
}

static void	process_tokens(char *input, t_token_list *tokens, int *i,
		int *is_first_word)
{
	size_t	len;

	len = ft_strlen(input);
	while (*i < (int)len)
	{
		if (input[*i] == '$')
			assign_dollar(input, i, tokens);
		else if (input[*i] == '|')
		{
			assign_pipe(input[*i], tokens);
			(*i)++;
		}
		else if (input[*i] == '<' || input[*i] == '>')
			assign_redirection(input, i, tokens);
		else if (input[*i] == '\'' || input[*i] == '"')
			handle_quoted_content(input, i, tokens, input[*i]);
		else
		{
			token_is_command(input, i, tokens, is_first_word);
			(*i)++;
		}
	}
}

void	assign_cmd_types(t_token *token)
{
	int	expecting_cmd;

	expecting_cmd = 1;
	while (token)
	{
		if (token->type == PIPE)
			expecting_cmd = 1;
		else if (expecting_cmd && (token->type == STRING || token->type == ENV
				|| token->type == DOLLAR))
		{
			token->type = CMD;
			expecting_cmd = 0;
		}
		else if (token->type == CMD || token->type == ARG)
			expecting_cmd = 0;
		token = token->next;
	}
}

t_token_list	*tokenize_input(char *input)
{
	t_token_list	*tokens;
	int				i;
	int				is_first_word;

	is_first_word = 1;
	tokens = NULL;
	if (!input || is_ignorable_input(input))
		return (NULL);
	if (!init_tokenizer(input, &tokens, &i))
		return (NULL);
	process_tokens(input, tokens, &i, &is_first_word);
	if (!tokens->head)
	{
		free(tokens);
		return (NULL);
	}
	assign_cmd_types(tokens->head);
	return (tokens);
}
