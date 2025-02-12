/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/02/12 15:13:36 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n\033[1;38;5;206mminishell$>\033[0m ");
	fflush(stdout);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tokens->next);
		free(tmp->input);
		free(tmp);
	}
}

int	main(void)
{
	char	*input;
	char	*prompt;
	char	*cmd;
	char	*args[] = {"ls", "-l", NULL};
	t_token	*tokens;

	cmd = "ls";
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = "\033[1;38;5;206mminishell$>\033[0m ";
		input = readline(prompt);
		if (input == NULL)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		printf("You entered: %s\n", input);
		tokens = tokenize_input(input);
		if(tokens)
			free_tokens(tokens);
		while (tokens)
		{
			printf("Type: %d\n, Value: %s\n", tokens->type, tokens->input);
			tokens = tokens->next;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free_tokens(tokens);
			free(input);
			break ;
		}
		if (ft_strcmp(input, "ls") == 0)
			exec_command(cmd, args);
		free(input);
	}
	if (tokens)
		free_tokens(tokens);
	return (0);
}
