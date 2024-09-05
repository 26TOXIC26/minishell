/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:57:24 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/30 04:05:59 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	printer(t_main *m, char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	m->exit_status = 1;
}

static void	up_pwd(t_main *m, char **oldpwd)
{
	char	*path;
	t_env	*pwd;
	t_env	*old_p;

	update_env("OLDPWD=", m);
	pwd = find_env_node(m->env, "PWD");
	old_p = find_env_node(m->env, "OLDPWD");
	if (old_p->line[1])
		free(old_p->line[1]);
	old_p->line[1] = (*oldpwd);
	path = get_pwd();
	if (pwd && path)
	{
		free(pwd->line[1]);
		pwd->line[1] = path;
	}
	else
		free(path);
}

void	ft_cd(t_main *m, t_command *cmd)
{
	char	*home;
	char	*oldpwd;

	if (cmd->options[1] && cmd->options[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		m->exit_status = 1;
		return ;
	}
	oldpwd = get_pwd();
	if (!cmd->options[1])
	{
		home = find_env_str("HOME", m->env);
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			m->exit_status = 1;
		}
		else if (chdir(home))
			printer(m, home);
	}
	else if (chdir(cmd->options[1]))
		printer(m, cmd->options[1]);
	up_pwd(m, &oldpwd);
}
