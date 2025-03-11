/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:54:06 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/10 14:37:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*

Fonction qui va split l'entree des commandes.
On va chercher separer les commandes pour mieux les traiter.

			PIPE
			/    \
		CMD      CMD
	ls -l    grep "hello"

*/
