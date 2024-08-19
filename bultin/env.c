/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/19 16:53:24 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(char *str, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	len = i;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len) && (env[i][len] == '='
			|| env[i][len] == '\0'))
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

char	**ft_init(char **env)
{
	int		i;
	int		len;
	char	**tmp;
	size_t	l;

	i = 0;
	while (env[i])
		i++;
	tmp = _malloc((i + 1) * sizeof(char *));
	tmp[i] = NULL;
	len = i;
	i = 0;
	while (i < len)
	{
		l = ft_strlen(env[i]);
		tmp[i] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(tmp[i], env[i], l + 1);
		i++;
	}
	return (tmp);
}

void	set_env(t_minishell *m, char **env)
{
	if (!*env || !env)
	{
		m->env = _malloc(sizeof(char *) * 4);
		//ft_collectore(col, m->env);
		m->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		m->env[1] = ft_strdup("SHLVL=1");
		m->env[2] = ft_strdup("_=/usr/bin/env");
		m->env[3] = NULL;
	}
	else
	{
		m->env = ft_init(env);
		
		plus_shlvl(find_env("SHLVL", m->env), m);
	}
}
