/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo_env_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:47:44 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 05:09:34 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*check_pwd(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->line[0], str))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->line[0]))
			return (tmp->line[1]);
		tmp = tmp->next;
	}
	return (NULL);
}
int	eq_posss(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	eq_pose(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
int add_env_app(char *str, t_main *m)
{
	t_env	*tmp;
	t_env	*new;
	char 	*key;
	char	*s;

	key = ft_strdup2(str, eq_pose(str, '+'));
	tmp = check_pwd(m->env, key);
	free (key);
	if (tmp)
	{
		s = ft_strdup(str + eq_pos(str) + 1);
		key = ft_strjoinss(tmp->line[1], s);
		free (s);
		tmp->line[1] = key;
		tmp->exp = 0;
	}
	else
	{
		new = creat_new_env(str, 0, '+');
		if (!new)
			return (0);
		ft_env_back(&(m->env), new);
	}
	return (0);
}
void	update_env(char *str, t_main *m)
{
	t_env *tmp;
	t_env *new;
	char *key;

	if (eq_posss(str, '+') && !add_env_app(str, m))
		return ;
	else
		key = ft_strdup2(str, eq_pos(str));
	tmp = check_pwd(m->env, key);
	free(key);
	if (tmp)
	{
		free(tmp->line[1]);
		key = ft_strdup(str + eq_pos(str) + 1);
		tmp->line[1] = key;
		tmp->exp = 0;
	}
	else
	{
		new = creat_new_env(str, 0, '=');
		if (!new)
			return ;
		ft_env_back(&(m->env), new);
	}
}