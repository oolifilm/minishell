/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:14 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/14 19:59:53 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern char		**g_env;

static size_t	count_env(void)
{
	size_t	i;

	i = 0;
	while (g_env[i])
		i++;
	return (i);
}

static void	free_env_arr(char **env, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static int	copy_env(char **new_env, size_t env_count)
{
	size_t	i;

	i = 0;
	while (i < env_count)
	{
		new_env[i] = ft_strdup(g_env[i]);
		if (!new_env[i])
		{
			free_env_arr(new_env, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_var(const char *var)
{
	char	**new_env;
	size_t	env_count;

	env_count = count_env();
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (1);
	if (copy_env(new_env, env_count))
		return (1);
	new_env[env_count] = ft_strdup(var);
	if (!new_env[env_count])
	{
		free_env_arr(new_env, env_count);
		return (1);
	}
	new_env[env_count + 1] = NULL;
	g_env = new_env;
	return (0);
}

static int	replace_var(const char *var, size_t var_len)
{
	size_t	i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], var, var_len) == 0 && g_env[i][var_len] == '=')
		{
			free(g_env[i]);
			g_env[i] = ft_strdup(var);
			if (!g_env[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (-1);
}

static int	process_var(const char *var)
{
	char	*equal_sign;
	size_t	var_len;

	if (!is_valid_env_var(var))
	{
		write(2, "export: '", 9);
		write(2, var, ft_strlen(var));
		write(2, "': not a valid identifier\n", 25);
		return (1);
	}
	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (0);
	var_len = equal_sign - var;
	if (replace_var(var, var_len) != -1)
		return (0);
	return (add_var(var));
}

int	ft_export(char **argv)
{
	size_t	i;

	if (!argv || !argv[0])
		return (1);
	if (!argv[1])
		return (print_sorted_env());
	i = 1;
	while (argv[i])
	{
		if (process_var(argv[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
