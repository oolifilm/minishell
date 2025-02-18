/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:31 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 11:04:30 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void add_string_token(char *input, int start, int end, t_token **head, t_token **cur)
{
    char temp[256];
    
    if (end > start)
    {
        ft_strncpy(temp, input + start, end - start);
        temp[end - start] = '\0';
        add_token(head, cur, temp, STRING);
    }
}

static void handle_double_quotes(char *input, int *i, t_token **head, t_token **cur, int *start)
{
    if (input[*i] == '$')
    {
        add_string_token(input, *start, *i, head, cur);
        assign_env_var(input, i, head, cur);
        *start = *i;
    }
    else
        (*i)++;
}

/*
Fonction qui va assigner les quotes.
On va verifier si on a une quote.
Si on a une quote, on va creer un nouveau token.
On va verifier si on a une double quote.
Si on a une double quote, on va creer un nouveau token.
*/

void	assign_quote(char input, t_token **head, t_token **cur)
{
	char	temp[2] = {input, '\0'};

	if (input == '\'')
	{
		add_token(head, cur, temp, SINGLE_QUOTE);
	}
	else if (input == '\"')
	{
		add_token(head, cur, temp, DOUBLE_QUOTE);
	}
}

void handle_quoted_content(char *input, int *i, t_token **head, t_token **cur, char quote_type)
{
    int start;

    (*i)++;
    start = *i;
    while(input[*i] && input[*i] != quote_type)
    {
        if (quote_type == '"')
            handle_double_quotes(input, i, head, cur, &start);
        else
            (*i)++;
    }
    add_string_token(input, start, *i, head, cur);
    if (input[*i] == quote_type)
        (*i)++;
    else
        fprintf(stderr, "minishell: syntax error\n");
}
