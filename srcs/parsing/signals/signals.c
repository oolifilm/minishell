/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:02 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 17:26:25 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	rl_replace_line(const char *text, int clear_undo);

void	handle_eof(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
/*
Fonction pour gerer le signal SIGINT (Ctrl+C).
Elle affiche un retour à la ligne et le prompt.
*/

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigint_handler;
	act.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &act, NULL);
}
