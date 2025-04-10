/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 16:24:21 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

t_token_list	*tokenize_input(char *input)
{
	int				i;
	t_token_list	*tokens;
	int				is_first_word;
	size_t			len;

	len = ft_strlen(input);
	i = 0;
	is_first_word = 1;
	if (has_unclosed_quote(input))
	{
		printf("[ERROR] Lexer found an unclosed quote.\n");
		return (NULL);
	}
	tokens = init_token_list();
	skip_spaces(input, &i);
	while (i < (int)len)
	{
		assign_dollar(input[i], tokens);
		assign_pipe(input[i], tokens);
		assign_redirection(input, &i, tokens);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, tokens, input[i]);
		else
		{
			token_is_command(input, &i, tokens, &is_first_word);
			i++;
		}
	}
	return (tokens);
}
