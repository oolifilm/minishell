/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:01 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/09 16:38:45 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin(t_token *token)
{
    if (token->type !=COMMAND)
        return ;
    if (ft_strcmp(token->input, "export") == 0)
    {
        ft_export(token->next);
        return;
    }
    if (ft_strcmp(token->input, "exit") == 0)
    {
        free(input);
        free_tokens(token);
        clear_history();
        ft_exit(NULL);
        return;
    }
    if (ft_strcmp(token->input, "echo") == 0)
    {
        ft_echo_is_command(token);
        return;
    }
    if (ft_strcmp(token->input, "env") == 0)
    {
        ft_env_is_command(token);
        return;
    }
    if (ft_strcmp(token->input, "cd") == 0)
    {
        ft_cd(token->next);
        return;
    }
    if (ft_strcmp(token->input, "pwd") == 0)
    {
        ft_pwd();
        return;
    }
    if (ft_strcmp(token->input, "unset") == 0)
    {
        ft_unset(token->next);
        return;
    }
    exec_command(token);
}
