/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:48:46 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/15 18:22:14 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*get_next_cmd(t_token *token)
{
	while (token && token->type != CMD)
		token = token->next;
	return (token);
}

static pid_t	left_cmd(t_shell *sh, t_token *cmd, char *input, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("minishell"), exit(1), 1);
		close(fd[1]);
		exec_cmd(sh, cmd, input);
		exit(0);
	}
	return (pid);
}

static pid_t	right_cmd(t_shell *sh, t_token *cmd, char *input, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("minishell"), exit(1), 1);
		close(fd[0]);
		exec_cmd(sh, cmd, input);
		exit(0);
	}
	return (pid);
}

int	exec_pipe(t_shell *sh, t_token *token, char *input)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	t_token	*cmd_right;

	while (token && token->type != PIPE)
		token = token->next;
	if (!token)
		return (1);
	cmd_right = get_next_cmd(token->next);
	if (!cmd_right)
		return (fprintf(stderr, "[ERROR] No command after pipe.\n"), 1);
	if (pipe(fd) < 0)
		return (perror("minishell"), 1);
	pid_left = left_cmd(sh, token, input, fd);
	if (pid_left < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	pid_right = right_cmd(sh, cmd_right, input, fd);
	if (pid_right < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
	return (0);
}

int	contains_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}
