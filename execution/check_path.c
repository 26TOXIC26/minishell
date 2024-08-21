/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:12:23 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 22:58:30 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_path(t_main *m)
{
	char	**path;
	t_env	*tmp;

	tmp = m->env;
	path = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line[0], "PATH", 4))
		{
			path = ft_split1(tmp->line[1], ':');
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*check_cmd_path(char *cmd, char **paths)
{
	int i;
	char *aux;
	char *tmp1;
	char *tmp2;

	if (!access(cmd, X_OK))
		return (cmd);
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp2 = ft_strdup(cmd);
		aux = ft_strjoin(paths[i], "/");
		tmp1 = ft_strjoin(aux, tmp1);
		free(aux);
		free(tmp2);
		if (!access(tmp1, X_OK))
			return (tmp1);
		free(tmp1);
		i++;
	}
	return (NULL);
}