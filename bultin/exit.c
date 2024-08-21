/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:00:10 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/21 00:41:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// minish->command->options[k]
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

void	ft_exit(t_main *m, int exits)
{
	if (m->command->options[1] && m->command->options[2])
	{
		printf("MINIHELL: exit: too many arguments\n");
		m->exit_status = 1;
	}
	else if (m->command->options[1] && !m->command->options[2])
	{
		if (check_num(m->command))
		{
			printf("MINIHELL: exit: %s: numeric argument required\n",
				m->command->options[1]);
			m->exit_status = 255;
			_clearmini(m, 255);
		}
		else
		{
			exits = ft_atoi(m->command->options[1]);
			_clearmini(m, exits);
		}
	}
	else
		_clearmini(m, 1);
}
