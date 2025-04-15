/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:35:29 by julien            #+#    #+#             */
/*   Updated: 2025/04/15 14:35:26 by leaugust         ###   ########.fr       */
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

t_shell	*init_shell(char **envp)
{
	t_shell	*sh;
	int		count;
	int		i;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	sh->env = malloc(sizeof(char *) * (count + 1));
	if (!sh->env)
	{
		free(sh);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		sh->env[i] = ft_strdup(envp[i]);
		if (!sh->env[i])
		{
			while (i > 0)
				free(sh->env[--i]);
			free(sh->env);
			free(sh);
			return (NULL);
		}
		i++;
	}
	sh->env[count] = NULL;
	sh->last_exit_status = 0;
	return (sh);
}

/* Boucle principale du shell, qui lit l'entrée utilisateur,
affiche un prompt et traite les commandes.*/

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	char			*prompt;
	t_token			*tmp;
	t_token_list	*tokens_list;
	t_shell			*sh;

	(void)argc;
	(void)argv;
	sh = NULL;
	set_sig_action();
	g_env = init_env(envp);
	sh = init_shell(envp);
	while (1)
	{
		prompt = "minishell$> ";
		input = readline(prompt);
		if (!input)
			handle_eof();
		add_history(input);
		tokens_list = tokenize_input(input);
		if (tokens_list && tokens_list->head)
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
			exec_cmd(sh, tmp, input);
		}
		else
		{
			free_tokens(tokens_list);
			free(input);
			continue ;
		}
		free(input);
		free_tokens(tokens_list);
	}
	return (0);
}
