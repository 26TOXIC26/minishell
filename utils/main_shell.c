/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:39:49 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/03 11:25:57 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_main	*_initminish(char **env)
{
	t_main	*minish;

	minish = _malloc(sizeof(t_main));
	minish->cmd = NULL;
	minish->command = NULL;
	minish->exit_status = 0;
	minish->paths = NULL;
	minish->bultin = i_bultin();
	minish->env = set_envc(env);
	return (minish);
}

void	bash_routine(t_main *m)
{
	m->mini.line = add_space(m->mini.line);
	m->cmd = init_cmd(m);
	if (!m->cmd)
		return ;
	if (count_her(m->cmd) > 16)
	{
		ft_putstr_fd("MINIHELL: maximum here-document count exceeded\n", 2);
		(_clearmini(m, 2), exit(2));
	}
	m->command = init_command(m->cmd, m);
	_execinit(m);
	free_cmd(m->cmd);
	free_comd(m->command);
}
