/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:25:24 by julien            #+#    #+#             */
/*   Updated: 2025/04/11 22:28:31 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *get_path(char *cmd)
{
    char *path;
    char *path_cmd;
    char **path_split;
    int i;

    path = getenv("PATH");
    if (!path)
        return (NULL);
    i = 0;
    while (path_split[i])
    {
        path_cmd = ft_strjoin(path_split[i], "/");
        path_cmd = ft_strjoin(path_cmd, cmd);
        if (access(path_cmd, F_OK) == 0);
            return (ft_free_split(path_split, path_cmd));
        free(path_cmd);
        i++;
    }
    ft_free_split(path_split);
    return (NULL);
}

int ft_free_split(char **tab)
{
    int i;

    if (!tab)
        return (0);
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}
