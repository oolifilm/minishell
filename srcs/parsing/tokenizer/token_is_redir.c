/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:09:13 by julien            #+#    #+#             */
/*   Updated: 2025/03/01 10:53:41 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void get_redir_file(char *input, int *i, t_token **head, t_token **cur)
{
    int start;
    char *file;

    (*i)++;
    while (input[*i] && input[*i] == ' ')
        (*i)++;
    start = *i;
    while (input[*i] && input[*i] != ' ' && input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
        (*i)++;
    if (*i > start)
    {
        file = ft_substr(input, start, *i - start);
        if (file)
        {
            add_token(head, cur, file, REDIR_FILE);
            free(file);
        }
    }
}

static void handle_output_redir(char *input, int *i, t_token **head, t_token **cur)
{
    char temp[3];
    
    temp[0] = '\0';
    temp[1] = '\0';
    temp[2] = '\0';
    if (input[*i + 1] == '>' && input[*i + 2] == '>')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
        *i = ft_strlen(input);
        return;
    }
    if (input[*i + 1] == '>')
    {
        temp[0] = input[*i];
        temp[1] = input[*i + 1];
        add_token(head, cur, temp, REDIR_APPEND);
        (*i)++;
    }
    else
    {
        temp[0] = input[*i];
        add_token(head, cur, temp, REDIR_OUTPUT);
    }
    get_redir_file(input, i, head, cur);
}

static void handle_input_redir(char *input, int *i, t_token **head, t_token **cur)
{
    char temp[3];

    temp[0] = '\0';
    temp[1] = '\0';
    temp[2] = '\0';
    if (input[*i + 1] == '<' && input[*i + 2] == '<')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
        *i = ft_strlen(input);
        return;
    }
    if (input[*i + 1] == '<')
    {
        temp[0] = input[*i];
        temp[1] = input[*i + 1];
        add_token(head, cur, temp, HEREDOC);
        (*i)++;
    }
    else
    {
        temp[0] = input[*i];
        add_token(head, cur, temp, REDIR_INPUT);
    }
    get_redir_file(input, i, head, cur);
}

void assign_redirection(char *input, int *i, t_token **head, t_token **cur)
{
    if (input[*i] == '>')
        handle_output_redir(input, i, head, cur);
    else if (input[*i] == '<')
        handle_input_redir(input, i, head, cur);
}
