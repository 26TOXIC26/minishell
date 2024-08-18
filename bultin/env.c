/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/18 11:40:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(char *str, t_minishell *mini)
{
	int		i;
	size_t	len;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	len = i;
	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], str, len) && (mini->env[i][len] == '='
			|| mini->env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	plus_shlvl(size_t i, t_minishell *mini)
{
	char	*str;
	char	*tmp;
	int		j;

	str = ft_strchr(mini->env[i], '=') + 1;
	j = ft_atoi(str);
	j++;
	tmp = ft_itoa(j);
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

void	ft_init(char **env, t_minishell *m, t_colec *col)
{
	int		i;
	int		len;
	size_t	l;

	i = 0;
	while (env[i])
		i++;
	m->env = _malloc((i + 1) * sizeof(char *));
	ft_collectore(&col, m->env);
	m->env[i] = NULL;
	len = i;
	i = 0;
	while (i < len)
	{
		l = ft_strlen(env[i]);
		m->env[i] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(m->env[i], env[i], l + 1);
		i++;
	}
}

void	_set_env(t_minishell *m, char **env, t_colec **col)
{
	if (!*env || !env)
	{
		m->env = _malloc(sizeof(char *) * 4);
		ft_collectore(col, m->env);
		m->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		m->env[1] = ft_strdup("SHLVL=1");
		m->env[2] = ft_strdup("_=/usr/bin/env");
		m->env[3] = NULL;
	}
	else
	{
		ft_init(env, m, *col);
		plus_shlvl(find_env("SHLVL", m), m);
	}
}
