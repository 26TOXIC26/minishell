/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:57:24 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/10 16:16:51 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printer(f_list *m, char *str)
{
	printf("cd: %s: No such file or directory\n", str);
	m->exit_status = 1;
}
int srch_pwd(char *str,char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			return (i);
	return(0);
}

void pwd_update(f_list *m)
{
	size_t i;
	
	i = srch_pwd("PWD=", m->mini.env);
	edit_pwd(i, &m->mini);
	i = srch_pwd("OLDPWD=", m->mini.env);
	edit_old_pwd(i, &m->mini);
}

char	*get_env(char *str, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
		{
			env[i] += 5;
			return ((env[i]));
		}
				
		i++;
	}
	return (NULL);
}

void	ft_cd(f_list *cmnd)
{
	char *home;
	
	if (!cmnd->command->options[1])
	{
		home = get_env("HOME", cmnd->mini.env);
		if (!home)
		{
			printf("cd: HOME not set\n");
			cmnd->exit_status = 1;
		}
		else
			if (chdir(home))
				printer(cmnd, home);
	}
	else
		if (chdir(cmnd->command->options[1]))
			printer(cmnd, cmnd->command->options[1]);
	pwd_update(cmnd);
}


