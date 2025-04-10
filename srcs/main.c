/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/04/11 17:55:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**g_env;

char	**create_argv_from_input(t_token_list *tokens)
{
	char	**argv;
	int		argc;
	t_token	*tmp;

	argv = malloc(sizeof(char *) * (tokens->size + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(tokens->head->input);
	if (!argv[0])
	{
		free(argv);
		return (NULL);
	}
	tmp = tokens->head->next;
	argc = 1;
	while (tmp)
	{
		if (tmp->input)
		{
			argv[argc] = ft_strdup(tmp->input);
			if (!argv[argc])
			{
				while (--argc >= 0)
					free(argv[argc]);
				free(argv);
				return (NULL);
			}
			argc++;
		}
		tmp = tmp->next;
	}
	argv[argc] = NULL;
	return (argv);
}

/* Boucle principale du shell, qui lit l'entrée utilisateur,
affiche un prompt et traite les commandes.*/

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	char			*prompt;
	t_token			*tmp;
	t_token_list	*tokens_list;

	(void)argc;
	(void)argv;
	set_sig_action();
	g_env = init_env(envp);
	while (1)
	{
		prompt = "minishell$> ";
		input = readline(prompt);
		if (!input)
			handle_eof();
		if (*input)
		{
			add_history(input);
			if (ft_strcmp(input, "clear") == 0)
				printf("\033[H\033[J");
		}
		tokens_list = tokenize_input(input);
		
		if (tokens_list)
		{
			if (!parse_tokens(tokens_list))
			{
				free_tokens(tokens_list);
				free(input);
				continue ;
			}
			tmp = tokens_list->head;
			while (tmp)
			{
				printf("Type: %s, Value: %s\n", get_token_type_str(tmp->type),
					tmp->input);
				tmp = tmp->next;
			}
			tmp = tokens_list->head;
			exec_builtin(tmp, input);
		}
		else
		{
			printf("[ERROR] tokenize_input returned NULL\n");
			continue ;
		}
		free(input);
		free_tokens(tokens_list);
		continue ;
	}
	return (0);
}


