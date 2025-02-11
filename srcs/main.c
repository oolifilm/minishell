/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/02/11 15:33:08 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Boucle pour lire l'entrée standard de l'utilisateur et pour afficher le prompt*/

int	main(void)
{
	char	*input;
	char	*prompt;
	char *cmd = "ls";
	char *args[] = {"ls", "-l", NULL};

	while (1)
	{
		prompt = "\033[1;38;5;206mminishell$>\033[0m ";
		input = readline(prompt);
        if (input == NULL)
		{
			free(input);
            break;
		}
		if (*input)
            add_history(input);
        printf("You entered: %s\n", input);
		t_token *tokens = tokenize_input(input);
		while(tokens)
		{
			printf("Type: %d\n, Value: %s\n", tokens->type, tokens->value);
			tokens = tokens->next;
		}
		if (ft_strcmp(input, "exit") == 0)
			break;
		if (ft_strcmp(input, "ls") == 0)
			exec_command(cmd, args);
        free(input);
	}
	return (0);
}
