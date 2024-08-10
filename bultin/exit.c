/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:00:10 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/10 16:18:02 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//minish->command->options[k]
int check_num(t_command *cmd)
{
    int i;
    int j;
    
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

void ft_exit(f_list *m)
{
    
    if (m->command->options[2])
	{
		printf("MINIHELL: exit: too many arguments\n");
		m->exit_status = 1;
	}
	else if (!m->command->options[2])
	{
		if (check_num(m->command))
		{
			printf("MINIHELL: exit: %s: numeric argument required\n",
				m->command->options[1]);
			m->exit_status = 255;
            _clearmini(m);
            exit(255);
		}
		else
		{
			m->exit_status = ft_atoi(m->command->options[1]);
            _clearmini(m);
			exit(m->exit_status);
		}
	}
	else
		_clearmini(m);
}