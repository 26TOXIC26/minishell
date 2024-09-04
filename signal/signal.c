/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 06:51:10 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/03 20:42:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_i;

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_i = 130;
	}
}

void	ig_signal(t_main *m, int i)
{
	if (i == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (i == 3)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (g_exit_i == 130)
		m->exit_status = g_exit_i;
	g_exit_i = 0;
}

void	sig_i_herdoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(2);
}
