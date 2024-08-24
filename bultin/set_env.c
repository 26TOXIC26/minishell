/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 03:59:28 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/24 00:50:29 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strchrs(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == s[i])
		return (i);
	return (i);
}
t_env	*creat_new_env(char *str, int exp)
{
	t_env	*new;
	char	*f_line;
	char	*s_line;
	
	s_line = NULL;
	f_line = ft_substr(str, 0, ft_strchrs(str, '='));
	if (ft_strchr(str, '='))
		s_line = ft_strdup(str + eq_pos(str) + 1);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->line[0] = f_line;
	new->line[1] = s_line;
	new->exp = exp;
	new->index = 0;
	new->next = NULL;
	return (new);
}

void	ft_env_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*new_env(void)
{
	t_env	*new;

	new = creat_new_env("OLDPWD", 1);
	ft_env_back(&new, creat_new_env(ft_strjoin("PWD=", getcwd(NULL, 0)), 0));
	ft_env_back(&new, creat_new_env("SHLVL=1", 0));
	ft_env_back(&new, creat_new_env("_=/usr/bin/env", 0));
	return (new);
}

t_env	*set_envc(char **env)
{
	int		i;
	int		check;
	t_env	*new;
	t_env	*envs;

	i = 0;
	if (!env || !*env)
		return (new_env());
	envs = creat_new_env(env[i], 0);
	i++;
	check = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			check++;
		new = creat_new_env(env[i], 0);
		ft_env_back(&envs, new);
		i++;
	}
	if (!check)
		ft_env_back(&envs, creat_new_env("OLDPWD", 1));
	return (envs);
}

