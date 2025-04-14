/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:30:30 by julien            #+#    #+#             */
/*   Updated: 2025/04/14 12:39:19 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int has_redirect(t_token *token)
{
    t_token *cur;

    cur = token;
    while(cur)
    {
        if (cur->type == REDIR_IN || cur->type == REDIR_OUT || cur->type == APPEND || cur->type == HEREDOC)
            return (1);
        cur = cur->next;
    }
    return (0);
}

char **fill_argv(t_token *token, char **argv)
{
    t_token *cur;
    int i;

    i = 1;
    cur = token->next;
    while (cur)
    {
        if (cur->type == STRING || cur->type == ARG || cur->type ==ENV || cur->type == EXIT)
            argv[i++] = expand_token(cur);
        cur = cur->next;
    }
    argv[i] = NULL;
    return (argv);
}

char **build_argv(t_token *token)
{
    char **argv;
    int count;
    t_token *cur;

    count = 1;
    cur = token->next;
    while (cur)
    {
        if (cur->type == STRING || cur->type == ARG || cur->type ==ENV || cur->type == EXIT)
            count++;
        cur = cur->next;
    }
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    argv[0] = ft_strdup(token->input);
    return (fill_argv(token, argv));
}

int handle_redirect(t_token *token)
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0)
    {
        if (handle_redirect(token) == -1)
            exit(1);
        exec_builtin(token, input);
        exit(0);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("minishell");
}
