/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:58:26 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/23 04:10:53 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
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
