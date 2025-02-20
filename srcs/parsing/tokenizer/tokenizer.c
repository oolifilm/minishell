/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:05 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/20 14:06:06 by jbanchon         ###   ########.fr       */
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
		assign_quote(input[i], &head, &cur);
		token_is_command(input, &i, &head, &cur, &is_first_word);
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_content(input, &i, &head, &cur, input[i]);
		i++;
	}
	if (!head)
		printf(YELLOW "[WARNING] No tokens were created!\n" RESET);
	return (head);
}
