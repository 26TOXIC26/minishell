/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 16:59:21 by bamssaye         ###   ########.fr       */
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
			if (ft_strncmp(tm[i], tm[j],
					ft_strlen(tm[i])) > 0)
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

void	export_solo(char *str, char **env)
{
	if (ch_exp(str, ft_strlen(str)))
		pexport_e(str);
	(void)env;
}
// int	ft_export2(t_command *cmd)
// {
// 	// t_minishell	*tmp;
// 	char	**cm;
// 	char	**tmp;
// 	int		i;

// 	cm = cmd->options;
// 	if (!cm[1])
// 	{
// 		tmp = ft_init(mini->env);
// 		sort_env(tmp);
// 		// print_env(tmp);
// 		arry_c(tmp);
// 	}
// 	i = 0;
// 	while (cm[++i])
// 	{
// 		if (!ch_eq(cm[i]))
// 			export_solo(cm[i], mini->env);
// 	}
// 	// if (cm[1] && !ft_isalpha(cm[1][0]) && cm[1][0] != '_')
// 	// 	pexport_e(cm[1]);
	
// 	return (0);
// }
int	ft_lstsizess(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	sort_env(t_env *env)
{
	int		i;
	int		j;
	char	**line;
	t_env 	*tmps;

	i = 0;
	i = ft_lstsizess(env);
	line = _malloc(sizeof(char*) * (i + 1));
	j = 0;
	tmps = env;
	while (tmps)
	{
		line[j++] = ft_strdup(tmps->line[0]);
		tmps = tmps->next;
	}
	line[j] = NULL;
	sort_env_1(line);
	
	i = -1;
	while (line[++i])
		fprintf(stderr, "%s\n", line[i]);
	// i = -1;
	// tmps = env;
	// while (tmps)
	// {
		
	// 	tmps = tmps->next;
	// }

	






	
}
void	ft_export(t_main *cmd, t_command *mini)
{
	// if (ft_export2(cmd) == 1)
	// 	return ;
	(void)mini;
	
	//t_env *sorted_list;
	sort_env(cmd->env);
	// sorted_list = merge_sort(cmd->env);
	//print_exp(cmd->env);
	// print_exp(cmd->env);	


	
	// while (cmd && cmd->type == 1)
	// {
	// 	ft_export_run(cmd, mini);
	// 	cmd = cmd->next;
	// }
}
