/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/05 05:56:25 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_pluse(char *str)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=' && !check)
			check++;
		else if (str[i] == '+' && str[i + 1] != '=' && !check)
			return (1);
	}
	if (check > 1)
		return (1);
	return (0);
}

static int	_checkexp(char *str, int f)
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
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && check_pluse(str))
			return (1);
		i++;
	}
	return (0);
}

static void	export_solo(char *flag, t_main *mini)
{
	if (_checkexp(flag, ft_strlen(flag)))
		mini->exit_status = pexport_e(flag);
	else
		ft_env_back(&mini->env, creat_new_env(flag, 1, '='));
}

int	find_char_indexs(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i++;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (str[i] == '+' && str[i + 1] == '=')
			return (i + 1);
		else if (str[i] != '_' && !ft_isalnum(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	ft_export(t_main *mini, t_command *cmd)
{
	int	i;
	int	equal;

	if (!cmd->options[1])
		sort_env(mini->env);
	i = 0;
	while (cmd->options[++i])
	{
		if (!find_char_indexs(cmd->options[i]))
			export_solo(cmd->options[i], mini);
		else
		{
			equal = find_char_indexs(cmd->options[i]);
			if (!equal || equal == -1)
				mini->exit_status = pexport_e(cmd->options[i]);
			else
			{
				if (_checkexp(cmd->options[i], equal))
					mini->exit_status = pexport_e(cmd->options[i]);
				else
					update_env(cmd->options[i], mini);
			}
		}
	}
}
