/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/07 08:48:04 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env(t_minishell *mini)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (mini->env[i])
	{
		j = i + 1;
		while (mini->env[j])
		{
			if (ft_strncmp(mini->env[i], mini->env[j],
					ft_strlen(mini->env[i])) > 0)
			{
				tmp = mini->env[i];
				mini->env[i] = mini->env[j];
				mini->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env(char **env, int export)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (export == 1)
		{
			printf("declare -x ");
			printf("%s\n", env[i]);
		}
		else if (export == 0 && ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}

void	ft_export_run(t_list *cmd, t_minishell *mini)
{
	int	i;

	if (ft_strchr(cmd->token, '+') && ft_strchr(cmd->token, '+')[1] == '=')
	{
		i = find_env(cmd->token, mini);
		mini->env[i] = ft_strjoin(mini->env[i], ft_strchr(cmd->token, '=') + 1);
	}
	else if (find_env(cmd->token, mini) == -1)
	{
		mini->env = ft_realloc(mini->env, (d2_len(mini->env) * sizeof(char *))
				+ sizeof(char *) + 1);
		mini->env[d2_len(mini->env) + 1] = NULL;
		mini->env[d2_len(mini->env)] = ft_strdup(cmd->token);
	}
	else
	{
		i = find_env(cmd->token, mini);
		free(mini->env[i]);
		mini->env[i] = ft_strdup(cmd->token);
	}
}

int	ft_export2(t_list *cmd, t_minishell *mini, t_colec *colec)
{
	t_minishell	*tmp;

	if (cmd && cmd->token[0] == '=')
	{
		printf("export: not a valid identifier\n");
		return (1);
	}
	if (!cmd || cmd->type != 1)
	{
		tmp = malloc(sizeof(t_minishell));
		ft_collectore(&colec, tmp);
		ft_init(mini->env, tmp);
		sort_env(tmp);
		print_env(tmp->env, 1);
	}
	return (0);
}

void	ft_export(t_list *cmd, t_minishell *mini, t_colec *colec)
{
	if (ft_export2(cmd, mini, colec) == 1)
		return ;
	while (cmd && cmd->type == 1)
	{
		ft_export_run(cmd, mini);
		cmd = cmd->next;
	}
}
