/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:22:45 by julien            #+#    #+#             */
/*   Updated: 2025/04/15 17:39:44 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern char	**g_env; // Same ici, refaire export sans g_env

static void	print_env_var_with_value(char *var, char *equal_sign)
{
	char	*var_name;
	size_t	name_len;

	name_len = equal_sign - var;
	var_name = malloc(name_len + 1);
	if (!var_name)
		return ;
	ft_strncpy(var_name, var, name_len);
	var_name[name_len] = '\0';
	write(1, "export ", 11);
	write(1, var_name, name_len);
	write(1, "=\"", 2);
	write(1, equal_sign + 1, ft_strlen(equal_sign + 1));
	write(1, "\"\n", 2);
	free(var_name);
}

void	print_env_var(char *var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		print_env_var_with_value(var, equal_sign);
	else
	{
		write(1, "export", 11);
		write(1, var, ft_strlen(var));
		write(1, "\n", 1);
	}
}

static char	**create_sorted_env(void)
{
	char	**sorted_env;
	size_t	env_count;
	size_t	i;

	env_count = 0;
	while (g_env[env_count])
		env_count++;
	sorted_env = malloc(sizeof(char *) * (env_count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		sorted_env[i] = g_env[i];
		i++;
	}
	sorted_env[env_count] = NULL;
	qsort(sorted_env, env_count, sizeof(char *), compare_vars); // A changer faire une sorte de bubble short ?
	return (sorted_env);
}

int	print_sorted_env(void)
{
	char	**sorted_env;
	size_t	i;

	sorted_env = create_sorted_env();
	if (!sorted_env)
		return (1);
	i = 0;
	while (sorted_env[i])
	{
		print_env_var(sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (0);
}
