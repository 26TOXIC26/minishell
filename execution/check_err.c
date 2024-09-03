/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:04:50 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/03 11:58:07 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	path_check(t_main *m, char *fpath, char *cmd)
{
	if (!fpath)
	{
		ft_putstr_fd("MINIHELL: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		m->exit_status = 127;
		exit(127);
	}
}

void	_pipe(t_main *m, t_command *cmd)
{
	int	i;

	if (cmd->next)
	{
		i = pipe(m->pipe_fd);
		if (i == -1)
		{
			ft_putstr_fd("MINIIHELL: ", 2);
			perror("pipe error");
			ft_putstr_fd("\n", 2);
			m->exit_status = 1;
			exit(1);
		}
	}
}

void	exec_check(t_main *m, char *path, char **cmd, char **env)
{
	int	i;

	i = execve(path, cmd, env);
	if (i == -1)
	{
		ft_putstr_fd("MINIHELL: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		m->exit_status = 126;
		exit(126);
	}
}
