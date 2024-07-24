/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:18:00 by pc                #+#    #+#             */
/*   Updated: 2024/06/15 03:54:03 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	d2_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	edit_old_pwd(size_t i, t_minishell *mini)
{
	char	*pwd;
	int		j;

	if ((int)i == -1)
	{
		j = d2_len(mini->env);
		pwd = getcwd(NULL, 0);
		mini->env[j] = malloc(sizeof(char) * (ft_strlen(pwd) + 8));
		ft_strlcpy(mini->env[j], "OLDPWD=", 8);
		ft_strlcpy(mini->env[j] + 7, pwd, ft_strlen(pwd) + 1);
		mini->env[j + 1] = NULL;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		free(mini->env[i]);
		mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 8);
		ft_strlcpy(mini->env[i], "OLDPWD=", 8);
		ft_strlcpy(mini->env[i] + 7, pwd, ft_strlen(pwd) + 1);
	}
}

void	edit_pwd(size_t i, t_minishell *mini)
{
	char	*pwd;
	int		j;

	if ((int)i == -1)
	{
		j = d2_len(mini->env);
		pwd = getcwd(NULL, 0);
		mini->env[j] = malloc(sizeof(char) * (ft_strlen(pwd) + 5));
		ft_strlcpy(mini->env[j], "PWD=", 5);
		ft_strlcpy(mini->env[j] + 4, pwd, ft_strlen(pwd) + 1);
		mini->env[j + 1] = NULL;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		free(mini->env[i]);
		mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 5);
		ft_strlcpy(mini->env[i], "PWD=", 5);
		ft_strlcpy(mini->env[i] + 4, pwd, ft_strlen(pwd) + 1);
	}
}

void	ft_init(char **env, t_minishell *mini)
{
	int		i;
	int		len;
	size_t	l;

	i = 0;
	mini->exit_status = 0;
	while (env[i])
		i++;
	mini->env = _malloc(sizeof(char *) * i + 1);
	mini->env[i] = NULL;
	len = i;
	i = -1;
	while (++i < len)
	{
		l = ft_strlen(env[i]);
		mini->env[i] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(mini->env[i], env[i], l + 1);
	}
}
