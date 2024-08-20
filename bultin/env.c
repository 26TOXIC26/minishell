/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/20 15:36:27 by bamssaye         ###   ########.fr       */
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
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->line[0])
			printf("declare -x %s", tmp->line[0]);
		if (tmp->line[1])
		{
			printf("=\"%s\"\n", tmp->line[1]);
		}
		else if (tmp->exp == 0)
		{
			printf("=\"\"\n");
		}
		else
			printf("\n");
		tmp = tmp->next;
	}
}
