/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:59:32 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/24 01:12:55 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_free(t_env **node)
{
	// int	i;
	if (!node || !*node)
		return ;
	// i = 0;
	(*node)->next = NULL;
	free((*node)->line[0]);
	free((*node)->line[1]);
	// free((*node)->line);
	free(*node);
	*node = NULL;
}
void	env_delete(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*node;

	if (!env || !*env || !str || !*str)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line[0], str, ft_strlen(str)))
		{
			node = tmp;
			tmp = tmp->next;
			*env = (*env)->next;
			node->next = NULL;
			env_free(&node);
		}
		else
			tmp = tmp->next;
	}
}
void	ft_unset(t_command *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd || !env || !*env)
		return ;
	if (!cmd->options[1])
		return ;
	while (cmd->options[i])
	{
		env_delete(env, cmd->options[i]);
		i++;
	}
}
