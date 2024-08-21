/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:59:32 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 14:57:46 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(char *str, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	len = i;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len) && (env[i][len] == '='
				|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(t_list *cmd, t_minishell *mini)
{
	(void)cmd;
	(void)mini;
	// 	t_list	*tmp;
	// 	int		i;
	// 	tmp = cmd;
	// 	while (tmp && !tmp->type)
	// 	{
	// 		i = find_env(tmp->token, mini->env);
	// 		if (i != -1)
	// 		{
	// 			free(mini->env[i]);
	// 			while (mini->env[i])
	// 			{
	// 				mini->env[i] = mini->env[i + 1];
	// 				i++;
	// 			}
	// 			mini->env[i] = NULL;
	// 		}
	// 		tmp = tmp->next;
	// 	}
}
