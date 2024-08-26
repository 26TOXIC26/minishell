/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:38:19 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/26 06:51:50 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	arry_c(char **str)
{
	int	i;

	if (!str || !*str)
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
	// arry_c(m->mini.env);
	// free_env(m->env);
	arry_c(m->bultin);
	arry_c(m->paths);
	free_env(m->env);
	// ft_lstclear_collec(&m->cmd, del_collec);
	rl_clear_history();
	if (f)
	{
		free_cmd(m->cmd);
		free_comd(m->command);
	}
	free(m);
	if (f)
		exit(f);
	// exit(0);
}
