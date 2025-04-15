/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:30:28 by julien            #+#    #+#             */
/*   Updated: 2025/04/15 18:27:42 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	exec_builtin_cmd(t_token *token, char *input)
{
	char	**argv;
	char	*cmd;

	(void)input;
	cmd = ft_strdup(token->input);
	if (!cmd)
		return (1);
	argv = build_argv(token);
	if (!argv)
	{
		free(cmd);
		return (1);
	}
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(argv);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(argv);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(argv);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(argv);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(argv);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(argv);
	free(cmd);
	ft_free_split(argv);
	return (0);
}

int	exec_builtin_redirect(t_token *token, char *input)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirect(token, input) == -1)
			exit(1);
		exec_builtin_cmd(token, input);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("minishell");
	return (0);
}

int	run_ext_child(t_shell *sh, t_token *token, char *path, char **argv)
{
	if (handle_redirect(token, NULL) == -1)
		exit(1);
	execve(path, argv, sh->env);
	handle_execve_err(path, argv);
	return (0);
}

int	exec_ext_cmd(t_shell *sh, t_token *token, char **argv)
{
	char	*path;
	pid_t	pid;

	path = get_path(argv[0]);
	if (!path)
	{
		perror("minishell");
		ft_free_split(argv);
		return (0);
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
	return (0);
}

void	exec_cmd(t_shell *sh, t_token *token, char *input)
{
	char	**argv;

	if (token->type != CMD)
		return ;
	if (contains_pipe(token))
	{
		exec_pipe(sh, token, input);
		return ;
	}
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
