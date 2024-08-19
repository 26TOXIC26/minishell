/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:38 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 17:56:43 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	sort_env(char **tm)
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

void	ft_export_run(t_command *cmd, char **env)
{
	
	(void)cmd;
	// (void)mini;
	(void)env;
//	int	i;

	// if (ft_strchr(cmd->token, '+') && ft_strchr(cmd->token, '+')[1] == '=')
	// {
	// 	i = find_env(cmd->token, env);
	// 	env[i] = ft_strjoin(env[i], ft_strchr(cmd->token, '=') + 1);
	// }
	// else if (find_env(cmd->token, env) == -1)
	// {
	// 	env = ft_realloc(env, (d2_len(env) * sizeof(char *))
	// 			+ sizeof(char *) + 1);
	// 	env[d2_len(env) + 1] = NULL;
	// 	env[d2_len(env)] = ft_strdup(cmd->token);
	// }
	// else
	// {
	// 	i = find_env(cmd->token, env);
	// 	free(env[i]);
	// 	env[i] = ft_strdup(cmd->token);
	// }
}
void	export_solo(char *str, char **env)
{
	if (ch_exp(str, ft_strlen(str)))
		pexport_e(str);
	(void)env;
}
int	ft_export2(t_command *cmd, t_minishell *mini)
{
	// t_minishell	*tmp;
	char	**cm;
	char	**tmp;
	int		i;

	cm = cmd->options;
	if (!cm[1])
	{
		tmp = ft_init(mini->env);
		sort_env(tmp);
		print_env(tmp, 1);
		arry_c(tmp);
	}
	i = 0;
	while (cm[++i])
	{
		if (!ch_eq(cm[i]))
			export_solo(cm[i], mini->env);
	}
	if (cm[1] && !ft_isalpha(cm[1][0]) && cm[1][0] != '_')
		pexport_e(cm[1]);
	
	return (0);
}

void	ft_export(t_command *cmd, t_minishell *mini)
{
	if (ft_export2(cmd, mini) == 1)
		return ;
	// while (cmd && cmd->type == 1)
	// {
	// 	ft_export_run(cmd, mini);
	// 	cmd = cmd->next;
	// }
}
