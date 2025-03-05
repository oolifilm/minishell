/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 14:49:33 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/* Boucle pour lire l'entrée standard de l'utilisateur et pour afficher le prompt*/

int	main(void)
{
	char	*input;
	char	*prompt;
	char	*cmd;
	char	*args[] = {"ls", "-l", NULL};
	t_token	*tmp;

	cmd = NULL;
	t_token_list *tokens_list;
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
		tokens_list = tokenize_input(input);
		if (!tokens_list)
		{
			printf("[ERROR] tokenize_input returned NULL\n");
			continue ;
		}
		tmp = tokens_list->head;
		while (tmp)
		{
			printf("Type: %s, Value: %s\n", get_token_type_str(tmp->type),
				tmp->input);
			tmp = tmp->next;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			free_tokens(tokens_list);
			clear_history();
			break ;
		}
		if (ft_strcmp(input, "ls") == 0)
			exec_command(cmd, args);
		free(input);
		free_tokens(tokens_list);
	}
	return (0);
}
