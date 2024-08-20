/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _builtin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:34:49 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 01:25:12 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	_bultin(t_main *mi)
// {
// 	if (!ft_strncmp("env", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		print_env(mi->mini.env, 0);
// 	else if (!ft_strncmp("echo", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_echo(mi->command->options);
// 	else if (!ft_strncmp("export", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_export(mi->cmd, &mi->mini, mi->colec);
// 	else if (!ft_strncmp("pwd", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_pwd();
// 	else if (!ft_strncmp("unset", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_unset(mi->cmd, &mi->mini);
// 	else if (!ft_strncmp("cd", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_cd(mi);
// 	else if (!ft_strncmp("exit", mi->command->options[0],
// 			ft_strlen(mi->command->options[0])))
// 		ft_exit(mi);
// }

void	_bultin(t_main *mi, t_command *cmd)
{
	char *opt;

	opt = cmd->options[0];
	// if (!ft_strncmp("export", opt, ft_strlen(opt)))
	// 	ft_export(cmd, &mi->mini);
	// else if (!ft_strncmp("echo", cmd->options[0], ft_strlen(cmd->options[0])))
	// 	ft_echo(mi->command->options);
	if (!ft_strncmp("env", cmd->options[0], ft_strlen(cmd->options[0])))
		print_env(mi->mini.env, 0);
	// else if (!ft_strncmp("pwd", cmd->options[0], ft_strlen(cmd->options[0])))
	// 	ft_pwd();
	// else if (!ft_strncmp("unset", cmd->options[0], ft_strlen(cmd->options[0])))
	// 	ft_unset(mi->cmd, &mi->mini);
	// else if (!ft_strncmp("cd", cmd->options[0], ft_strlen(cmd->options[0])))
	// 	ft_cd(mi);
	// else if (!ft_strncmp("exit", cmd->options[0], ft_strlen(cmd->options[0])))
    //     ft_exit(mi);
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
