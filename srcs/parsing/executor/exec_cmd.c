/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:30:28 by julien            #+#    #+#             */
/*   Updated: 2025/04/11 22:22:06 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int exec_builtin_redirect(t_token *token, char *input)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (handle_redirect(token) == -1)
            exit(1);
        exec_builtin_cmd(token, input);
        exit(0);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("minishell");
}

int handle_execve_err(char *path, char **argv)
{
    perror("minishell");
    free(path);
    ft_free_split(argv);
    exit(1);
}

int run_ext_child(t_shell *sh, t_token *token, char *path, char **argv)
{
    if (handle_redirect(token) == -1)
        exit(1);
    execve(path, argv, sh->env);
    handle_execve_err(path, argv);
}

int exec_ext_cmd(t_shell *sh, t_token *token, char **argv)
{
    char *path;
    pid_t pid;

    path = get_path(argv[0]);
    if (!path)
    {
        perror("minishell");
        ft_free_split(argv);
        return ;
    }
    pid = fork();
    if (pid == 0)
        run_ext_child(sh, token, path, argv);
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    else
    {
        perror("minishell");
        free(path);
        ft_free_split(argv);
        exit(1);
    }
    free(path);
    ft_free_split(argv);
}

void exec_cmd(t_shell *sh, t_token *token, char *input)
{
    char **argv;

    if (token->type != CMD)
        return ;
    expand_token_list(token);
    if (is_builtin(token->input))
    {
        if (has_redirect(token))
            exec_builtin_redirect(token, input);
        else
            exec_builtin_cmd(token, input);
        return ;
    }
    argv = build_argv(token);
    if (!argv)
        return ;
    exec_ext_cmd(sh, token, argv);
}
