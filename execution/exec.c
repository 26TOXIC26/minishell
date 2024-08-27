/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:35:31 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/27 18:49:43 by bamssaye         ###   ########.fr       */
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
		if (!ft_strncmp(m->bultin[i], cmd, ft_strlen(cmd)))
			if (ft_strlen(m->bultin[i]) == ft_strlen(cmd))
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
void	_waitall(int *status)
{
	int	pid;

	pid = wait(status);
	while (pid > 0)
		pid = wait(status);
}

void	_execinit(t_main *m)
{
	t_command *cmd;
	int st;
	int tin;
	int tout;

	tin = dup(STDIN_FILENO);
	tout = dup(STDOUT_FILENO);
	m->paths = get_path(m);
	cmd = m->command;
	//_heardoc(m);
	if (!cmd->next && is_bltn(m, cmd->options[0]))
	{
		if (cmd->redir->file)
			open_rfile(m, cmd->redir);
		_bultin(m, cmd);
		r_std(&tin, &tout);
	}
	else
	{
		_execution(m, &tin, &tout, &cmd);
		r_std(&tin, &tout);
		_waitall(&st);
		m->exit_status = WEXITSTATUS(st);
	}
}