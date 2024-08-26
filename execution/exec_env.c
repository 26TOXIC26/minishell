/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:50:33 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/26 04:30:54 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*full_line(t_env *s_env)
{
	char	*str;
	char	*str2;

	if (!s_env || !s_env->line[0])
		return (NULL);
	str = ft_strdup(s_env->line[0]);
	str2 = ft_strjoin(str, "=");
	free(str);
	if (s_env->line[1])
	{
		str = ft_strjoin(str2, s_env->line[1]);
		free(str2);
		return (str);
	}
	else
		return (str2);
}

char	**exec_env(t_main *m)
{
	char	**env;
	int		i;
	t_env	*s_env;

	if (!m || !m->env)
		return (NULL);
	s_env = m->env;
	env = malloc(sizeof(char *) * (ft_lstsizess(s_env) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (s_env)
	{
		env[i] = full_line(s_env);
		i++;
		s_env = s_env->next;
	}
	env[i] = NULL;
	return (env);
}


