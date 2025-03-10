/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 16:32:22 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
__Fonctionnement :__

Initialise une nouvelle liste chaînée de tokens (t_token_list).

1. Alloue dynamiquement une structure t_token_list.
2. Vérifie si l'allocation a échoué et retourne NULL en cas d'échec.
3. Initialise les pointeurs :
   - head à NULL (début de la liste vide).
   - cur à NULL (aucun token actuel).
4. Retourne le pointeur vers la liste nouvellement créée.
*/

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

/*
__Fonctionnement :__

Boucle principale du shell, qui lit l'entrée utilisateur, affiche un prompt et traite les commandes.

1. Affiche un prompt personnalisé en couleur (minishell$>).
2. Lit l'entrée utilisateur via readline().
   - Si EOF (Ctrl+D) est détecté, affiche un message et quitte proprement.
   - Si l'entrée n'est pas vide, elle est ajoutée à l'historique (add_history).
   - Gère la commande clear pour effacer l'écran.
3. Affiche l'entrée utilisateur pour le débogage.
4. Tokenise l'entrée avec tokenize_input().
   - Si la tokenisation échoue, affiche un message d'erreur et passe à l'itération suivante.
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
	char	*input;
	char	*prompt;
	char	*args[] = {"ls", "-l", NULL};
	t_token	*tmp;
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
		if (tmp && tmp->type == COMMAND)
		{
			if (ft_strcmp(tmp->input, "cd") == 0)
			{
				char *args[3] = {"cd", NULL, NULL};
				if (tmp->next)
					args[1] = tmp->next->input;
				ft_cd(args);
				ft_pwd((char *[]){"pwd", NULL}); // Afficher le nouveau répertoire
			}
			else if (ft_strcmp(tmp->input, "pwd") == 0)
			{
				ft_pwd((char *[]){"pwd", NULL});
			}
			else
			{
				while (tmp)
				{
					printf("Type: %s, Value: %s\n", get_token_type_str(tmp->type),
						tmp->input);
					tmp = tmp->next;
				}
			}
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			free_tokens(tokens_list);
			clear_history();
			break ;
		}
		if (ft_strcmp(input, "ls") == 0)
			exec_command("ls", args);
		free(input);
		free_tokens(tokens_list);
	}
	return (0);
}
