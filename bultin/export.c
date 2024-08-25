/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/25 22:58:02 by bamssaye         ###   ########.fr       */
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
	print_exp(env);
}
void	export_solo(char *flag, t_main *mini)
{
	if (ch_exp(flag, ft_strlen(flag)))
		pexport_e(flag);
	else
	{
		ft_env_back(&mini->env, creat_new_env(flag, 1));
	}
}
int	_checkexp(char *str, int f)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (1);
	else
		i++;
	while (str[i] && i < f)
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
void	ft_export(t_main *mini, t_command *cmd)
{
	int	i;
	int	equal;

	i = 1;
	if (!cmd->options[1])
		sort_env(mini->env);
	while (cmd->options[i])
	{
		if (!ch_eq(cmd->options[i]))
			export_solo(cmd->options[i], mini);
		else
		{
			equal = eq_pos(cmd->options[i]);
			if (!equal)
				pexport_e(cmd->options[i]);
			else
			{
				if (_checkexp(cmd->options[i], equal))
					pexport_e(cmd->options[i]);
				else
					update_env(cmd->options[i], mini);
			}
		}
		i++;
	}
}
