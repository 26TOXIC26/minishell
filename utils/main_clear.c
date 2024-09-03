/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:38:19 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/03 11:23:17 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	arry_c(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	_clearmini(t_main *m, int f)
{
	free(m->mini.line);
	arry_c(m->bultin);
	arry_c(m->paths);
	free_env(m->env);
	rl_clear_history();
	if (f)
	{
		free_cmd(m->cmd);
		free_comd(m->command);
	}
	free(m);
}
