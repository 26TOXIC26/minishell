/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:34:49 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/24 05:58:40 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_bultin(f_list *mi)
{
	if (ft_strncmp("env", mi->command->options[0], ft_strlen(mi->command->options[0])))
		print_env(mi->mini.env, 0);
	else if (ft_strncmp("echo", mi->command->options[0], ft_strlen(mi->command->options[0])))
		ft_echo(mi->command->options);
	else if (ft_strncmp("export", mi->command->options[0], ft_strlen(mi->command->options[0])))
		ft_export(mi->cmd, &mi->mini);
	else if (ft_strncmp("pwd", mi->command->options[0], ft_strlen(mi->command->options[0])))
		ft_pwd();
	else if (ft_strncmp("unset", mi->command->options[0], ft_strlen(mi->command->options[0])))
		ft_unset(mi->cmd, &mi->mini);
	else if (ft_strncmp("cd", mi->command->options[0], ft_strlen(mi->command->options[0])))
		ft_cd(mi->cmd);
	else if (ft_strncmp("exit", mi->command->options[0], ft_strlen(mi->command->options[0])))
		// exit
}
