/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/05 13:58:12 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token_list	*tokenize_input(char *input)
{
	int		i;
	t_token_list *tokens;
	int		is_first_word;
	size_t	len;

	len = ft_strlen(input);
	i = 0;
	is_first_word = 1;
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
