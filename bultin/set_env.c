/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 03:59:28 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 19:41:31 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*creat_new_env(char *str, int exp, char c)
{
	t_env	*new;
	char	*f_line;
	char	*s_line;

	s_line = NULL;
	f_line = ft_substr(str, 0, get_index_char(str, c));
	if (ft_strchr(str, '='))
		s_line = ft_strdup(str + find_char_index(str, '=') + 1);
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

static t_env	*set_empty_env(void)
{
	t_env	*new;
	char	*tmp;
	char	*pwd;

	new = creat_new_env("OLDPWD", 1, '=');
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	ft_env_back(&new, creat_new_env(pwd, 0, '='));
	ft_env_back(&new, creat_new_env("SHLVL=1", 0, '='));
	ft_env_back(&new, creat_new_env("_=/usr/bin/env", 0, '='));
	free(tmp);
	free(pwd);
	return (new);
}

static void	plus_shlvl(char *env)
{
	char	*str;
	char	*tmp;
	int		j;

	str = ft_strchr(env, '=') + 1;
	j = ft_atoi(str);
	j++;
	tmp = ft_itoa(j);
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

t_env	*set_envc(char **env)
{
	int		i;
	int		check;
	t_env	*new;
	t_env	*envs;

	i = 0;
	if (!env || !*env)
		return (set_empty_env());
	envs = creat_new_env(env[i], 0, '=');
	i++;
	check = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			check++;
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			plus_shlvl(env[i]);
		new = creat_new_env(env[i], 0, '=');
		ft_env_back(&envs, new);
		i++;
	}
	if (!check)
		ft_env_back(&envs, creat_new_env("OLDPWD", 1, '='));
	return (envs);
}
