/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:37:30 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 22:54:46 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_empty_env(t_minishell *mini)
{
	mini->env = _malloc(sizeof(char *) * 4);
	mini->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	mini->env[1] = ft_strdup("SHLVL=1");
	mini->env[2] = ft_strdup("_=/usr/bin/env");
	mini->env[3] = NULL;
}

t_main	*_initminish(void)
{
	t_main	*minish;

	minish = _malloc(sizeof(t_main));
	minish->cmd = NULL;
	minish->colec = NULL;
	minish->command = NULL;
	minish->exit_status = 0;
	minish->bultin = i_bultin();
	return (minish);
}