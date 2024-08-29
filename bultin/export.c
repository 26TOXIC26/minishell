/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 20:29:40 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	pexport_e(char *str, t_main *m)
{
	printf("export: \'%s\': not a valid identifier\n", str);
	m->exit_status = 1;
}

static int check_pluse(char *str)
{
	int i;
	int check;

	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=' && !check)
			check++;
		else
			if (str[i] == '+' && str[i + 1] != '=' && !check)
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
		pexport_e(flag, mini);
	else
		ft_env_back(&mini->env, creat_new_env(flag, 1, '='));
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
		if (!find_char_index(cmd->options[i], '='))
			export_solo(cmd->options[i], mini);
		else
		{
			equal = find_char_index(cmd->options[i], '=');
			if (!equal)
				pexport_e(cmd->options[i], mini);
			else
			{
				if (_checkexp(cmd->options[i], equal))
					pexport_e(cmd->options[i], mini);
				else
					update_env(cmd->options[i], mini);
			}
		}
		i++;
	}
}
