/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/28 11:46:37 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*tokenize_input(char *input)
{
	int		i;
	t_token	*head;
	t_token	*cur;
	int		is_first_word;
	size_t len;

	len = ft_strlen(input);
	i = 0;
	is_first_word = 1;
	head = NULL;
	cur = NULL;
	skip_spaces(input, &i);	
	while (i < (int)len)
	{
		assign_dollar(input[i], &head, &cur);
		assign_pipe(input[i], &head, &cur);
		assign_redirection(input, &i, &head, &cur);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, &head, &cur, input[i]);
		else
		{
			token_is_command(input, &i, &head, &cur, &is_first_word);
			i++;
		}
	}
	return (head);
}
