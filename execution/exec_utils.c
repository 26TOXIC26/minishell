/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:46:25 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/07 10:07:21 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*check_all(t_command *cmd, t_main *m)
{
	struct stat	s_filestat;
	char		*paths;

	if (!stat(cmd->options[0], &s_filestat))
	{
		if (S_ISDIR(s_filestat.st_mode))
		{
			write(2, cmd->options[0], ft_strlen(cmd->options[0]));
			write(2, ": Is a directory\n", 17);
			exit(126);
		}
	}
	if (find_char_index(cmd->options[0], '/'))
		return (ft_strdup(cmd->options[0]));
	else
	{
		paths = check_path(cmd->options[0], m->paths);
		path_check(m, paths, cmd->options[0]);
		return (paths);
	}
	return (NULL);
}

static void	exec_child(t_main *m, t_command *cmd, int *pipe_fd)
{
	char	*paths;
	char	*cmmd;

	sig_child();
	paths = NULL;
	cmmd = cmd->options[0];
	if (cmd->options && cmd->options[0] && cmd->options[0][0] == '\0')
		exit(0);
	if (cmd->next != NULL)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (cmd->redir)
		open_rfile(m, cmd->redir);
	if (cmmd && !is_bltn(m, cmd->options[0]))
	{
		paths = check_all(cmd, m);
	}
	if (cmmd && !is_bltn(m, cmd->options[0]))
		exec_check(m, paths, cmd->options, exec_env(m));
	else if (cmmd && is_bltn(m, cmd->options[0]))
		_bultin(m, cmd);
	exit(0);
}

static void	exec_parent(t_command **cmd, int *fd_pip)
{
	if (!(*cmd)->next)
		close(STDIN_FILENO);
	else
	{
		close(fd_pip[1]);
		dup2(fd_pip[0], STDIN_FILENO);
		close(fd_pip[0]);
	}
	*cmd = (*cmd)->next;
}

void	_execution(t_main *m, int *tin, int *tout, t_command **cmd)
{
	int	pid;

	while (*cmd)
	{
		sig_ignor();
		_pipe(m, *cmd);
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("MINIIHELL: ", 2);
			perror("fork error");
			ft_putstr_fd("\n", 2);
			m->exit_status = 1;
			exit(1);
		}
		if (pid == 0)
		{
			close(*tin);
			close(*tout);
			exec_child(m, *cmd, m->pipe_fd);
		}
		else
			exec_parent(cmd, m->pipe_fd);
	}
}
