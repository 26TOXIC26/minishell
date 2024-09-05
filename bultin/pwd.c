/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:26 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/30 04:18:11 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(int *ex, t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s \n", pwd);
	else
		printf("%s \n", find_env_node(env, "PWD")->line[1]);
	free(pwd);
	*ex = 0;
}

char	*get_pwd(void)
{
	char	cwd[1024];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd = ft_strdup(cwd);
		return (pwd);
	}
	else
		return (NULL);
}
