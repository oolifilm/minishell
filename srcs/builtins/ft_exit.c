/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:11 by jbanchon          #+#    #+#             */
/*   Updated: 2025/02/12 14:44:04 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Ce qui nous est démandé dans le sujet : exit with no options
Commande exit : quitter le shell
Utilisation : exit [status]
*/

int	ft_exit(char **argv)
{
	int	status;

	(void)argv;
	status = 0;
	printf("exit from minishell: %d\n", status);
	exit(status);
}
