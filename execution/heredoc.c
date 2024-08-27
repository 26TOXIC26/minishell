/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:41:24 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/27 23:18:52 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_creatfile_n(t_redir *file, int *n)
{
	int i;
	
	i = 0;
	file->h_n[0] = '/';
	file->h_n[1] = 't';
	file->h_n[2] = 'm';
	file->h_n[3] = 'p';
	file->h_n[4] = '/';
	file->h_n[5] = 'f';
	file->h_n[6] = i + '0';
	file->h_n[7] = *n + '0';
	file->h_n[8] = '\0';
	*n = *n + 1;
}
int	check_del(t_redir *f, char *line)
{
	if (ft_strlen(f->file) == ft_strlen(line))
		if (!ft_strncmp(f->file, line, ft_strlen(line)))
			return (free(line), 1);
	return (0);
}
void	ch_expand(t_main *m, t_redir *f, int *fd, char *line)
{
	(void) m;
	(void) f;
	// (void) line;
	// char	*expanded;

	if (f->flag == 1)
	{
		// expanded = expand(line, m);
		// if (expanded)
		// {
		// 	write(*fd, expanded, ft_strlen(expanded));
		// 	free(expanded);
		// }
	}
	else
		write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
	// return;
}
void	l_heredoc(t_main *m, int *fd, t_redir *file)
{
	pid_t	pid;
	int		st;
	char	*gline;

	pid = fork();
	if (!pid)
	{
		while (1)
		{
			gline = readline("> ");
			if (!gline)
				break ;
			if (check_del(file, gline))
				break ;
			else
				ch_expand(m, file, fd, gline);
			free(gline);
		}
		exit(0);
	}
	else
		waitpid(pid, &st, 0);
}
void	_heredoc(t_main *m)
{
	t_command *cmd;
	t_redir *file;
	int fd;
	int n;

	cmd = m->command;
	n =  0;
	while (cmd)
	{
		file = cmd->redir;
		while (file)
		{
			if (file->type == HEREDOC)
			{
				_creatfile_n(file, &n);
				fprintf(stderr, "jjjj%s\n", file->h_n);
				fd = _openfile_hd(m, file->type, file->h_n);
				l_heredoc(m, &fd, file);
				close(fd);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
}
