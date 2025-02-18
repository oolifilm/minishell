/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:39:41 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 11:04:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int get_env_var_name(char *input, int j, char *var_name)
{
    int var_len;

    var_len = 0;
    j++;
    while(input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
    {
        var_name[var_len++] = input[j];
        var_len++;
        j++;
    }    
    var_name[var_len] = '\0';
    return (j);
}

static int cal_quoted_len(char *input, int j)
{
    int len;
    char var_name[256];
    char *env_value;

    len = 0;
    while (input[j] && input[j] != '"')
    {
        if (input[j] == '$' && input[j + 1])
        {
            j = get_env_var_name(input, j, var_name);
            env_value = getenv(var_name);
            if (env_value)
                len += ft_strlen(env_value);
            j--;
        }
        else
            len++;
        j++;
    }
    return (len);
}

static void fill_quoted_content(char *input, char *result, int *i)
{
    int j;
    int len;
    char var_name[256];
    char *env_value;

    j = *i + 1;
    len = 0;
    while (input[j] && input[j] != '"')
    {
        if (input[j] == '$' && input[j + 1])
        {
            j = get_env_var_name(input, j, var_name);
            env_value = getenv(var_name);
            if (env_value)
            {
                ft_strlcpy(result + len, env_value, ft_strlen(env_value) + 1);
                len += ft_strlen(env_value);
            }
            j--;
        }
        else
        {
            result[len] = input[j];
            len++;
        }
        j++;
    }
    result[len] = '\0';
    *i = j;
}

static char *handle_double_quoted(char *input, int *i)
{
    char *result;
    int j;
    int len;

    j = *i + 1;
    len = cal_quoted_len(input, j);
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    fill_quoted_content(input, result, i);
    return (result);
}
