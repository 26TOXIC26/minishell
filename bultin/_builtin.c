/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:34:49 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/03 10:37:53 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_bultin(t_main *mi, t_command *cmd)
{
	char	*opt;

	opt = cmd->options[0];
	if (!ft_strcmp("export", opt))
		ft_export(mi, cmd);
	else if (!ft_strcmp("env", opt))
		print_env(mi->env, &mi->exit_status);
	else if (!ft_strcmp("echo", opt))
		ft_echo(cmd->options, &mi->exit_status);
	else if (!ft_strcmp("pwd", opt))
		ft_pwd(&mi->exit_status, mi->env);
	else if (!ft_strcmp("unset", opt))
		ft_unset(mi->command, &mi->env, &mi->exit_status);
	else if (!ft_strcmp("cd", opt))
		ft_cd(mi, cmd);
	else if (!ft_strcmp("exit", opt))
		ft_exit(mi, 0, cmd);
}

char	**i_bultin(void)
{
	char	**b_in;

	b_in = malloc(8 * sizeof(char *));
	if (!b_in)
		return (NULL);
	b_in[0] = ft_strdup("echo");
	b_in[1] = ft_strdup("cd");
	b_in[2] = ft_strdup("pwd");
	b_in[3] = ft_strdup("export");
	b_in[4] = ft_strdup("unset");
	b_in[5] = ft_strdup("env");
	b_in[6] = ft_strdup("exit");
	b_in[7] = NULL;
	return (b_in);
}
