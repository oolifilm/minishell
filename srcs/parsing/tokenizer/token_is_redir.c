/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:09:13 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 14:49:28 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	get_redir_file(char *input, int *i, t_token_list *tokens)
{
	int		start;
	char	*file;

	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '|')
		(*i)++;
	if (*i > start)
	{
		file = ft_substr(input, start, *i - start);
		if (file)
		{
			add_token(tokens, file, REDIR_FILE);
			free(file);
		}
	}
}

static void	handle_output_redir(char *input, int *i, t_token_list *tokens)
{
	char	temp[3];

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	if (input[*i + 1] == '>' && input[*i + 2] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		*i = ft_strlen(input);
		return ;
	}
	if (input[*i + 1] == '>')
	{
		temp[0] = input[*i];
		temp[1] = input[*i + 1];
		add_token(tokens, temp, REDIR_APPEND);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_OUTPUT);
	}
	get_redir_file(input, i, tokens);
}

static void	handle_input_redir(char *input, int *i, t_token_list *tokens)
{
	char	temp[3];

	temp[0] = '\0';
	temp[1] = '\0';
	temp[2] = '\0';
	if (input[*i + 1] == '<' && input[*i + 2] == '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		*i = ft_strlen(input);
		return ;
	}
	if (input[*i + 1] == '<')
	{
		temp[0] = input[*i];
		temp[1] = input[*i + 1];
		add_token(tokens, temp, HEREDOC);
		(*i)++;
	}
	else
	{
		temp[0] = input[*i];
		add_token(tokens, temp, REDIR_INPUT);
	}
	get_redir_file(input, i, tokens);
}

void	assign_redirection(char *input, int *i, t_token_list *tokens)
{
	if (input[*i] == '>')
		handle_output_redir(input, i, tokens);
	else if (input[*i] == '<')
		handle_input_redir(input, i, tokens);
}
