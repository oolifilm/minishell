/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:14 by jbanchon          #+#    #+#             */
/*   Updated: 2025/03/17 11:02:14 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern char	**environ;

static int	replace_var(const char *var, size_t var_len)
{
	size_t	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, var_len) == 0
			&& environ[i][var_len] == '=')
		{
			free(environ[i]);
			environ[i] = ft_strdup(var);
			if (!environ[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (-1);
}

static char	**create_env_copy(size_t size)
{
	char	**new_env;
	size_t	i;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[size] = NULL;
	return (new_env);
}

static int	add_var(const char *var)
{
	char	**new_env;
	size_t	env_count;
	size_t	i;

	env_count = 0;
	while (environ[env_count])
		env_count++;
	new_env = create_env_copy(env_count);
	if (!new_env)
		return (1);
	new_env[env_count] = ft_strdup(var);
	if (!new_env[env_count])
	{
		i = 0;
		while (i < env_count)
			free(new_env[i++]);
		free(new_env);
		return (1);
	}
	new_env[env_count + 1] = NULL;
	environ = new_env;
	return (0);
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
