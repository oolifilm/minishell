/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/18 11:04:37 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*tokenize_input(char *input)
{
	int		i;
	t_token	*head;
	t_token	*cur;
	int		is_first_word;

	i = 0;
	is_first_word = 1;
	head = NULL;
	cur = NULL;
	skip_spaces(input, &i);
	while (input[i])
	{
		assign_dollar(input[i], &head, &cur);
		assign_pipe(input[i], &head, &cur);
		assign_redirection(input, &i, &head, &cur);
		assign_quote(input[i], &head, &cur);
		token_is_command(input, &i, &head, &cur, &is_first_word);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, &head, &cur, input[i]);
		i++;
	}
	return (head);
}
