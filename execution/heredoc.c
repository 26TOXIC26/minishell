/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:41:24 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/03 10:06:54 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_del(t_redir *f, char *line)
{
	if (ft_strlen(f->file) == ft_strlen(line))
		if (!ft_strncmp(f->file, line, ft_strlen(line)))
			return (free(line), 1);
	return (0);
}

static void	ch_expand(t_main *m, t_redir *f, int *fd, char *line)
{
	char	*expanded;

	if (f->flag == 0)
	{
		expanded = her_expand(line, m);
		if (expanded)
		{
			write(*fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else
		write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
}

static pid_t	l_heredoc(t_main *m, t_redir *file)
{
	pid_t	pid;
	int		fd;
	char	*gline;

	pid = fork();
	if (!pid)
	{
		fd = _openfile_hd(m, file->type, file->h_n);
		sig_herdoc();
		while (1)
		{
			gline = readline("$> ");
			if (!gline)
				break ;
			if (check_del(file, gline))
				break ;
			else
				ch_expand(m, file, &fd, gline);
			free(gline);
		}
		exit(0);
	}
	return (pid);
}

static int	_filehandler(t_redir *file, t_main *m, int *n)
{
	pid_t	pid;
	int		st;

	while (file)
	{
		if (file->type == HEREDOC)
		{
			_creatfile_n(file, n);
			pid = l_heredoc(m, file);
			waitpid(pid, &st, 0);
			if (WEXITSTATUS(st) == 2)
				return (m->exit_status = 130, 1);
		}
		file = file->next;
	}
	return (0);
}

int	_heredoc(t_main *m)
{
	t_command	*cmd;
	t_redir		*file;
	int			n;

	cmd = m->command;
	n = 0;
	sig_ignor();
	while (cmd)
	{
		file = cmd->redir;
		if (_filehandler(file, m, &n))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
