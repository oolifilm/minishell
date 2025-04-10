/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:50:01 by jbanchon          #+#    #+#             */
/*   Updated: 2025/04/10 17:37:55 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

char	**create_argv_from_token(t_token *token)
{
	int		count;
	t_token	*cur;
	int		i;
	char	**argv;

	cur = token;
	count = 0;
	while (cur)
	{
		if (cur->type != REDIR_IN && cur->type != REDIR_OUT
			&& cur->type != APPEND && cur->type != HEREDOC
			&& cur->type != REDIR_FILE)
			count++;
		cur = cur->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	cur = token;
	while (cur)
	{
		if (cur->type != REDIR_IN && cur->type != REDIR_OUT
			&& cur->type != APPEND && cur->type != HEREDOC
			&& cur->type != REDIR_FILE)
		{
			argv[i++] = ft_strdup(cur->input);
		}
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	execute_builtin_cmd(t_token *token, char *input)
{
	char	**argv;

	argv = create_argv_from_token(token);
	if (!argv)
		return (0);
	if (ft_strcmp(token->input, "export") == 0)
		ft_export(argv);
	else if (ft_strcmp(token->input, "exit") == 0)
	{
		free(input);
		clear_history();
		ft_exit(argv);
		free(argv);
		return (1);
	}
	else if (ft_strcmp(token->input, "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(token->input, "env") == 0)
		ft_env(argv);
	else if (ft_strcmp(token->input, "cd") == 0)
		ft_cd(argv);
	else if (ft_strcmp(token->input, "pwd") == 0)
		ft_pwd(argv);
	else if (ft_strcmp(token->input, "unset") == 0)
		ft_unset(argv);
	else
	{
		free(argv);
		return (0);
	}
	free(argv);
	return (1);
}

void	exec_builtin(t_token *token, char *input)
{
	pid_t	pid;
	t_token	*redir_token;

	if (token->type != CMD)
		return ;
	if (is_builtin(token->input))
	{
		if (has_redirection(token))
		{
			pid = fork();
			if (pid == 0)
			{
				redir_token = token->next;
				while (redir_token)
				{
					if (redir_token->type == REDIR_IN
						|| redir_token->type == REDIR_OUT
						|| redir_token->type == APPEND
						|| redir_token->type == HEREDOC)
					{
						if (exec_redirection(redir_token) == -1)
						{
							perror("minishell");
							exit(1);
						}
					}
					redir_token = redir_token->next;
				}
				execute_builtin_cmd(token, input);
				exit(0);
			}
			else if (pid > 0)
				waitpid(pid, NULL, 0);
			else
				perror("minishell");
		}
		else
			execute_builtin_cmd(token, input);
	}
	else
		exec_command(token);
}
