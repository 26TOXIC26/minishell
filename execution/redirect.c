/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:34:30 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 23:50:16 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_ambiguous(char *fname, t_main *m)
{
	ft_putstr_fd("MINIHELL: ", 2);
	ft_putstr_fd(fname, 2);
	ft_putstr_fd(": ambiguous redirect", 2);
	ft_putstr_fd("\n", 2);
	m->exit_status = 1;
	exit(1);
	return (1);
}

int	_openfile(t_main *m, int r_type, char *fname, int flag)
{
	int	fd;

	fd = 777;
	if (flag)
		return (_ambiguous(fname, m));
	else
	{
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
			m->exit_status = 1;
			exit(1);
		}
	}
	return (fd);
}

int	_openfile_hd(t_main *m, int f, char *fname)
{
	int	fd;

	fd = 777;
	if (f == HEREDOC)
		fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(fname, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		m->exit_status = 127;
		exit(127);
	}
	return (fd);
}

void	open_rfile(t_main *m, t_redir *files)
{
	t_redir	*file;
	int		fd;

	file = files;
	while (file)
	{
		if (file->type >= OUT && file->type <= HEREDOC)
		{
			if (file->type == HEREDOC)
				fd = _openfile(m, file->type, file->h_n, file->flag);
			else
				fd = _openfile(m, file->type, file->file, file->flag);
			if (file->type == IN || file->type == HEREDOC)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		file = file->next;
	}
}
