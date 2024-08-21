/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/20 23:51:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->exp == 0)
		{
			if (tmp->line[0])
				printf("%s=", tmp->line[0]);
			if (tmp->line[1])
				printf("%s\n", tmp->line[1]);
		}
		tmp = tmp->next;
	}
}
void	print_exp(t_env	*env)
{
	int		i;
	t_env	*tmps;
	int		len;

	i = 0;
	len = ft_lstsizess(env);
	while (i < len)
	{
		tmps = env;
		while (tmps)
		{
			if (tmps->index == i)
			{
				if (tmps->line[0][0] == '_' && !tmps->line[0][1])
					break;
				printf("declare -x %s=\"%s\"\n", tmps->line[0], tmps->line[1]);
				break ;
			}
			tmps = tmps->next;
		}
		i++;
	}
}
