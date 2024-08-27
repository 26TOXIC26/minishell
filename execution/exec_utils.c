/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:46:25 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/27 20:01:37 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_pipe(t_main *m, t_command *cmd)
{
	if (cmd->next)
	{
		pipe(m->pipe_fd);
		if (pipe(m->pipe_fd) == -1)
		{
			ft_putstr_fd("MINIIHELL: ", 2);
			perror("pipe error");
			ft_putstr_fd("\n", 2);
			m->exit_status = 1;
			exit(1);
		}
	}
}

void	exec_parent(t_command **cmd, int *fd_pip)
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
void	path_check(t_main *m, char *fpath, char *cmd)
{
	if (!fpath)
	{
		ft_putstr_fd("MINIHELL: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		m->exit_status = 127;
		exit(127);
	}
}
void	exec_check(t_main *m, char *path, char **cmd, char **env)
{
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_putstr_fd("MINIHELL: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		m->exit_status = 126;
		exit(126);
	}
}
void	_bultins(t_main *mi, t_command *cmd)
{
	char	*opt;

	opt = cmd->options[0];
	(void)mi;
	// if (!ft_strcmp("export", opt))
	// 	ft_export(mi, cmd);
	// else if (!ft_strcmp("env", opt))
	// 	print_env(mi->env);
	if (!ft_strcmp("echo", opt))
		ft_echo(cmd->options);
	else if (!ft_strcmp("pwd", opt))
		ft_pwd();
	// else if (!ft_strcmp("unset", opt))
	// 	ft_unset(mi->command, &mi->env);
	// else if (!ft_strcmp("cd", opt))
	// 	ft_cd(mi);
	// else if (!ft_strcmp("exit", opt))
	// 	ft_exit(mi, 0);
}
void exec_child(t_main *m, t_command *cmd, int *pipe_fd)
{
	char	*paths;
	char	*cmmd;
	
	cmmd = cmd->options[0];
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
		paths = check_path(cmd->options[0], m->paths);
		path_check(m, paths, cmd->options[0]);
	}
	if (cmmd && !is_bltn(m, cmd->options[0]))
		exec_check(m, paths, cmd->options, exec_env(m));
	else if (cmmd && is_bltn(m, cmd->options[0])){
		_bultin(m, cmd);
	}
	exit(0);
}

void	_execution(t_main *m, int *tin, int *tout, t_command **cmd)
{
	int pid;

	while (*cmd)
	{
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