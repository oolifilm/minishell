/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:03:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/01 10:28:28 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
        return (perror("minishell"), -1);
    while ((line = readline("> ")) != NULL)
    {
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
        return (close(pipe_fd[0]), -1);
    return(close(pipe_fd[0]), 0)
}

static int handle_output_redir(char *filename, int append)
{
    int fd;
    int flags;

    flags = O_WRONLY | O_CREAT;
    if (append)
        flags = flags | O_APPEND;
    else
        flags = flags | O_TRUNC;
    fd = open(filename, flags, 0664);
    if (fd == -1)
        return (perror("minishell"), -1);
    if (dup2(fd, STDOUT_FILENO) == -1)
        return (perror("minishell"), close(fd), -1);
    return (close(fd), 0);
}

static int handle_input_redir(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("minishell");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int exec_redirection(t_token *token)
{
    if (!token || !token->next || !token->next->input)
        return (-1);
    if (token->type == REDIR_INPUT)
        return (handle_input_redir(token->next->input));
    else if (token->type == REDIR_OUTPUT)
        return (handle_output_redir(token->next->input, 0));
    else if (token->type == REDIR_APPEND)
        return (handle_output_redir(token->next->input, 1));
    else if (token->type == HEREDOC)
        return (handle_heredoc(token->next->input));
    return (-1);
}
