/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:00:10 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/30 04:37:42 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_num(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->options[++i])
	{
		j = -1;
		while (cmd->options[i][++j])
			if (!ft_isdigit(cmd->options[i][j]))
				return (1);
	}
	return (0);
}

void	ft_exit(t_main *m, int exits, t_command *cmd)
{
	if (cmd->options[1] && cmd->options[2])
	{
		ft_putstr_fd("MINIHELL: exit: too many arguments\n", 2);
		m->exit_status = 1;
	}
	else if (cmd->options[1] && !cmd->options[2])
	{
		if (check_num(cmd))
		{
			ft_putstr_fd("MINIHELL: exit: ", 2);
			ft_putstr_fd(cmd->options[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			m->exit_status = 2;
			_clearmini(m, 2);
		}
		else
		{
			exits = ft_atoi(cmd->options[1]);
			_clearmini(m, exits);
		}
	}
	else
		_clearmini(m, 1);
}
