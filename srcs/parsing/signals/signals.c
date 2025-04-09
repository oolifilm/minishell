/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/09 12:08:35 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
Fonction pour gerer le signal SIGINT (Ctrl+C).
Elle affiche un retour à la ligne et le prompt.
*/

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell$> ", 14);
}

/*
Fonction pour configurer le gestionnaire de signal SIGINT.
On initialise une structure sigaction et met a 0 tous les bits de la structure
On veut invoquer la routine sigint_handler
lorsque le signal SIGINT est reçu.
On utilise sigaction pour enregistrer le gestionnaire de signal.
*/

void	set_sig_action(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}
