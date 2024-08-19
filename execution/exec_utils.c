/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:46:25 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 18:00:48 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void _pipe(t_main *m, t_command *cmd)
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

void exec_parent(t_command **cmd, int *fd_pip)
{
    if (!(*cmd)->next)
        close (STDIN_FILENO);
    else
    {
        close (fd_pip[1]);
        dup2(fd_pip[0], STDIN_FILENO);
        close (fd_pip[0]);
    }
    *cmd = (*cmd)->next;
}

void        _execution(t_main *m, int *tin, int *tout, t_command **cmd)
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