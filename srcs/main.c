/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 14:58:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Boucle pour lire l'entrée standard de l'utilisateur et pour afficher le prompt*/

int	main(void)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;
	char	*cmd;
	char	*args[] = {"ls", "-l", NULL};
	t_token	*tmp;

	cmd = "ls";
	while (1)
	{
		prompt = "\033[1;38;5;206mminishell$>\033[0m ";
		input = readline(prompt);
		if (!input)
		{
			printf(RED "[DEBUG] EOF detected, exiting...\n" RESET);
			exit(0);
		}
		if (*input)
		{
			add_history(input);
			if (ft_strcmp(input, "clear") == 0)
				printf("\033[H\033[J");
		}
		printf("You entered: %s\n", input);
		tokens = tokenize_input(input);
		if (!tokens)
		{
			printf("[ERROR] tokenize_input returned NULL\n");
			continue ;
		}
		tmp = tokens;
		while (tmp)
		{
			printf("Type: %s\n, Value: %s\n", get_token_type_str(tmp->type),
				tmp->input);
			tmp = tmp->next;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			free_tokens(tokens);
			clear_history();
			break ;
		}
		if (ft_strcmp(input, "ls") == 0)
			exec_command(cmd, args);
		free(input);
		free_tokens(tokens);
	}
	return (0);
}
