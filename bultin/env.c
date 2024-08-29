/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/29 20:21:04 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->exp == 0)
		{
			if (tmp->line[0])
				printf("%s", tmp->line[0]);
			if (tmp->line[1])
				printf("=%s\n", tmp->line[1]);
		}
		tmp = tmp->next;
	}
}

void	print_exp(t_env *env)
{
	int		i;
	t_env	*tmps;
	int		len;

	i = -1;
	len = size_env(env);
	while (++i < len)
	{
		tmps = env;
		while (tmps)
		{
			if (tmps->index == i)
			{
				if (tmps->line[0][0] == '_' && !tmps->line[0][1])
					break ;
				printf("declare -x %s", tmps->line[0]);
				if (tmps->line[1])
					printf("=\"%s\"\n", tmps->line[1]);
				else
					printf("\n");
				break ;
			}
			tmps = tmps->next;
		}
	}
}
