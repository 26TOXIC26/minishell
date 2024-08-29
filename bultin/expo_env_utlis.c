/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo_env_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:47:44 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 20:24:18 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_index(char **line, t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (line[i])
	{
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(line[i], tmp->line[0]))
			{
				tmp->index = i;
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

static void	sort_env_1(char **tm)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tm[i])
	{
		j = i + 1;
		while (tm[j])
		{
			if (ft_strncmp(tm[i], tm[j], ft_strlen(tm[i])) > 0)
			{
				tmp = tm[i];
				tm[i] = tm[j];
				tm[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sort_env(t_env *env)
{
	int		i;
	int		j;
	char	**line;
	t_env	*tmps;

	i = size_env(env);
	line = _malloc(sizeof(char *) * (i + 1));
	j = 0;
	tmps = env;
	while (tmps)
	{
		line[j++] = ft_strdup(tmps->line[0]);
		tmps = tmps->next;
	}
	line[j] = NULL;
	sort_env_1(line);
	set_index(line, env);
	arry_c(line);
	print_exp(env);
}

int	add_env_app(char *str, t_main *m)
{
	t_env	*tmp;
	t_env	*new;
	char	*key;
	char	*s;

	key = strdup_limit(str, find_char_index(str, '+'));
	tmp = find_env_node(m->env, key);
	free(key);
	if (tmp)
	{
		s = ft_strdup(str + find_char_index(str, '=') + 1);
		key = strjoing_f1(tmp->line[1], s);
		free(s);
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
	t_env	*tmp;
	t_env	*new;
	char	*key;

	if (find_equ_pluse(str, '+') && !add_env_app(str, m))
		return ;
	else
		key = strdup_limit(str, find_char_index(str, '='));
	tmp = find_env_node(m->env, key);
	free(key);
	if (tmp)
	{
		free(tmp->line[1]);
		key = ft_strdup(str + find_char_index(str, '=') + 1);
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
