/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:34:49 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/21 00:32:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_bultin(t_main *mi, t_command *cmd)
{
	char *opt;

	opt = cmd->options[0];
	if (!ft_strncmp("export", opt, ft_strlen(opt)))
		ft_export(mi, cmd);
	else if (!ft_strncmp("env", opt, ft_strlen(opt)))
		print_env(mi->env);
	else if (!ft_strncmp("echo", opt, ft_strlen(opt)))
		ft_echo(mi->command->options);
	else if (!ft_strncmp("pwd", opt, ft_strlen(opt)))
		ft_pwd();
	else if (!ft_strncmp("unset", opt, ft_strlen(opt)))
		ft_unset(mi->cmd, &mi->mini);
	else if (!ft_strncmp("cd", opt, ft_strlen(opt)))
		ft_cd(mi);
	else if (!ft_strncmp("exit", opt, ft_strlen(opt)))
        ft_exit(mi, 0);
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
