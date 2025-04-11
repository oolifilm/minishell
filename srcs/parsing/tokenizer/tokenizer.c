/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/11 17:49:12 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
			assign_pipe(input[*i], tokens);
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

t_token_list	*tokenize_input(char *input)
{
	t_token_list	*tokens;
	int				i;
	int				is_first_word;

	is_first_word = 1;
	if (!init_tokenizer(input, &tokens, &i))
		return (NULL);
	process_tokens(input, tokens, &i, &is_first_word);
	return (tokens);
}
