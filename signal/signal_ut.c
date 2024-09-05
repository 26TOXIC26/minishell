/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 06:55:36 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/05 06:55:50 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_i_herdoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(2);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_herdoc(void)
{
	signal(SIGINT, sig_i_herdoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_ignor(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
