/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/21 00:01:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env_1(char **tm)
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

void	set_index(char **line, t_env *env)
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
void	sort_env(t_env *env)
{
	int		i;
	int		j;
	char	**line;
	t_env	*tmps;

	i = ft_lstsizess(env);
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
}
void	ft_export(t_main *cmd, t_command *mini)
{
	// if (ft_export2(cmd) == 1)
	// 	return ;
	(void)mini;
	// t_env *sorted_list;
	sort_env(cmd->env);
	// sorted_list = merge_sort(cmd->env);
	print_exp(cmd->env);
	// print_exp(cmd->env);
	// while (cmd && cmd->type == 1)
	// {
	// 	ft_export_run(cmd, mini);
	// 	cmd = cmd->next;
	// }
}
