/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:46:45 by julien            #+#    #+#             */
/*   Updated: 2025/04/14 19:59:47 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid_env_var(const char *var)
{
	char	*equal_sign;
	size_t	i;

	if (!var || !*var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (1);
	i = 1;
	while (var + i < equal_sign)
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	compare_vars(const void *a, const void *b)
{
	const char	*var1;
	const char	*var2;
	size_t		len1;
	size_t		len2;

	var1 = *(const char **)a;
	var2 = *(const char **)b;
	if (ft_strchr(var1, '='))
		len1 = ft_strchr(var1, '=') - var1;
	else
		len1 = ft_strlen(var1);
	if (ft_strchr(var2, '='))
		len2 = ft_strchr(var2, '=') - var2;
	else
		len2 = ft_strlen(var2);
	if (len1 < len2)
		return (ft_strncmp(var1, var2, len1));
	return (ft_strncmp(var1, var2, len2));
}

char	**init_env(char **envp)
{
	size_t	count;
	char	**new_env;
	size_t	i;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}
