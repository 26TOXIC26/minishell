/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:34:30 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 18:03:28 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// # define PIPE 1
// # define OUT 2
// # define IN 3
// # define APPEND 4
// # define HEREDOC 5
// # define RFILE 6
int	_openfile(t_main *m, int r_type, char *fname)
{
	int	fd;

	fd = 777;
	if (r_type == IN || r_type == HEREDOC)
		fd = open(fname, O_RDONLY);
	else if (r_type == OUT)
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r_type == APPEND)
		fd = open(fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("MINIHELL: ", 2);
		ft_putstr_fd(fname, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		m->exit_status = 127;
		exit(127);
	}
	return (fd);
}

void open_rfile(int *_exit, t_redir *files)
{
    t_redir *file;
    int fd;

    file = files;
    while (file->next)
    {
        if (file->type >= OUT && file->type <= HEREDOC)
        {
            if (file->type == HEREDOC)
                fd = _openfile(_exit, file->type, file->h_n);
            else
                fd = _openfile(_exit, file->type, file->file);
            if (file->type == IN || file->type == HEREDOC)
                dup2(fd, STDIN_FILENO);
            else
                dup2(fd, STDOUT_FILENO);
        }
        file = file->next;
    }
}


