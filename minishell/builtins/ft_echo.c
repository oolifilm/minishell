/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:14:58 by jbanchon          #+#    #+#             */
/*   Updated: 2025/01/29 17:58:06 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : echo with option -n
=================================================================================
Commande echo : Doit écrire les entrées sur la sortie standard et avec l'option
Option -n : -n n'affiche pas la nouvelle ligne à la fin. Sinon affiche un retour à la ligne.
=================================================================================
Utilisation UNIX de la commande echo : echo [OPTIONS] [TEXTE].
*/

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

/*int	main(void)
{
	// Test case 1: No arguments
	char *args1[] = {"echo", NULL};
	printf("Test 1:\n");
	ft_echo(args1);

	// Test case 2: Single argument
	char *args2[] = {"echo", "Hello, world!", NULL};
	printf("Test 2:\n");
	ft_echo(args2);

	// Test case 3: Multiple arguments
	char *args3[] = {"echo", "Hello,", "world!", NULL};
	printf("Test 3:\n");
	ft_echo(args3);

	// Test case 4: -n option with single argument
	char *args4[] = {"echo", "-n", "Hello, world!", NULL};
	printf("Test 4:\n");
	ft_echo(args4);

	// Test case 5: -n option with multiple arguments
	char *args5[] = {"echo", "-n", "Hello,", "world!", NULL};
	printf("Test 5:\n");
	ft_echo(args5);

	return (0);
}*/