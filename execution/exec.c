/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:35:31 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/06 11:34:39 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_bltn(t_main *m, char *cmd)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	i = -1;
	while (m->bultin[++i])
		if (!ft_strcmp(m->bultin[i], cmd))
			return (1);
	return (0);
}

void	r_std(int *tin, int *tout)
{
	dup2(*tin, STDIN_FILENO);
	close(*tin);
	dup2(*tout, STDOUT_FILENO);
	close(*tout);
}

static void	wait_all(pid_t pid, t_main *m)
{
	int	status;

	while (waitpid(pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status))
			m->exit_status = 128 + WTERMSIG(status);
		if (WIFEXITED(status))
			m->exit_status = WEXITSTATUS(status);
	}
}

void	_execinit(t_main *m)
{
	t_command	*cmd;

	int (tin), (tout);
	tin = dup(STDIN_FILENO);
	tout = dup(STDOUT_FILENO);
	m->paths = get_path(m);
	cmd = m->command;
	if (_heredoc(m))
		return ;
	if (!cmd->next && is_bltn(m, cmd->options[0]))
	{
		if (cmd->redir)
			open_rfile_bu(m, cmd->redir);
		else
			_bultin(m, cmd);
		r_std(&tin, &tout);
	}
	else
	{
		_execution(m, &tin, &tout, &cmd);
		r_std(&tin, &tout);
		wait_all(0, m);
	}
}
