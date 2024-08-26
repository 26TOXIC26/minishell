/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:57:46 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/26 06:01:05 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **str)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	fprintf(stderr, "++++dsadsadasd+\n");
	while (str[i] && !ft_strncmp(str[i], "-n", 2) && is_n(str[i] + 2))
	{
		new_line = 1;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!new_line)
		printf("\n");
}
