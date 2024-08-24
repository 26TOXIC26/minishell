/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:57:24 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/24 00:48:31 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printer(t_main *m, char *str)
{
	printf("cd: %s: No such file or directory\n", str);
	m->exit_status = 1;
}

void	up_pwd(t_main *m, char **oldpwd)
{
	char	*path;
	t_env	*pwd;
	t_env	*old_p;

	update_env("OLDPWD=", m);
	pwd = check_pwd(m->env, "PWD");
	old_p = check_pwd(m->env, "OLDPWD");
	if (old_p->line[1])
		free(old_p->line[1]);
	old_p->line[1] = (*oldpwd);
	path = get_pwd();
	if (pwd)
	{
		free(pwd->line[1]);
		pwd->line[1] = path;
	}
	else
		free(path);
}
void	ft_cd(t_main *cmnd)
{
	char	*home;
	char	*opt;
	char	*oldpwd;

	opt = cmnd->command->options[1];
	oldpwd = get_pwd();
	if (!opt)
	{
		home = get_env("HOME", cmnd->env);
		if (!home)
		{
			printf("cd: HOME not set\n");
			cmnd->exit_status = 1;
		}
		else if (chdir(home))
			printer(cmnd, home);
	}
	else if (chdir(opt))
		printer(cmnd, opt);
	up_pwd(cmnd, &oldpwd);
}
