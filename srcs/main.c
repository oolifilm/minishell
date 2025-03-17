/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/03/13 10:44:43 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_argv_from_input(t_token_list *tokens)
{
	char	**argv;
	int		argc;
	t_token	*tmp;

	// Allouer un élément de plus pour argv[0] qui sera le nom de la commande
	argv = malloc(sizeof(char *) * (tokens->size + 2));
	if (!argv)
		return (NULL);

	// Initialiser argv[0] avec le nom de la commande
	argv[0] = ft_strdup(tokens->head->input);
	if (!argv[0])
	{
		free(argv);
		return (NULL);
	}

	// Copier les arguments à partir de argv[1]
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

/*
__Fonctionnement :__

Boucle principale du shell, qui lit l'entrée utilisateur,
	affiche un prompt et traite les commandes.

1. Affiche un prompt personnalisé en couleur (minishell$>).
2. Lit l'entrée utilisateur via readline().
   - Si EOF (Ctrl+D) est détecté, affiche un message et quitte proprement.
   - Si l'entrée n'est pas vide, elle est ajoutée à l'historique (add_history).
   - Gère la commande clear pour effacer l'écran.
3. Affiche l'entrée utilisateur pour le débogage.
4. Tokenise l'entrée avec tokenize_input().
   - Si la tokenisation échoue,
	affiche un message d'erreur et passe à l'itération suivante.
   - Parcourt et affiche la liste des tokens obtenus.
5. Vérifie si l'utilisateur a entré exit, et si oui :
   - Libère l'entrée et les tokens,
   - Efface l'historique,
   - Quitte la boucle.
6. Exécute ls -l si la commande ls est détectée.
7. Libère la mémoire allouée (input et tokens_list) avant la prochaine itération.
8. Retourne 0 en fin d'exécution.
*/

int	main(void)
{
	char			*input;
	char			*prompt;
	t_token			*tmp;
	t_token_list	*tokens_list;
	char			**args;

	while (1)
	{
		prompt = "\033[1;38;5;206mminishell$>\033[0m ";
		input = readline(prompt);
		if (!input)
		{
			printf("[DEBUG] EOF detected, exiting...\n");
			exit(0);
		}
		if (*input)
		{
			add_history(input);
			if (ft_strcmp(input, "clear") == 0)
				printf("\033[H\033[J");
		}
		// printf("%s\n", input);
		tokens_list = tokenize_input(input);
		if (!tokens_list)
		{
			printf("[ERROR] tokenize_input returned NULL\n");
			continue ;
		}
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
		args = create_argv_from_input(tokens_list);
		tmp = tokens_list->head;
		if (tmp && tmp->type == COMMAND && ft_strcmp(tmp->input, "export") == 0)
		{
			fprintf(stderr, "DEBUG: Calling ft_export with args\n");
			ft_export(args);
		}
		handle_command(tokens_list);
		ft_unset_is_command(tokens_list);
		ft_echo_is_command(tokens_list);
		ft_env_is_command(tokens_list);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			free_tokens(tokens_list);
			clear_history();
			ft_exit(NULL);
		}
		if (ft_strcmp(input, "ls") == 0)
			exec_command("ls", NULL);
		free(input);
		free_tokens(tokens_list);
	}
	return (0);
}
