/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:07:33 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/05 04:22:41 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_quotes3(char *str, int *i, int *j, char *new_str)
{
	char	qoute;

	qoute = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != qoute)
	{
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i] == qoute)
		(*i)++;
}

char	*remove_quotes2(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = _malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			remove_quotes3(str, &i, &j, new_str);
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	remove_quotes(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type != RFILE)
			tmp->token = remove_quotes2(tmp->token);
		tmp = tmp->next;
	}
}

int	in_quotes(char *str, int i, char c)
{
	int	flag;

	flag = 0;
	while (i >= 0)
	{
		if (str[i] == '\"')
		{
			i--;
			while (i >= 0 && str[i] != '\"')
			{
				if (str[i] == c)
					flag = 1;
				i--;
			}
			if (i < 0 && flag == 1)
				return (0);
			else
				i--;
			flag = 0;
		}
		else
			i--;
	}
	return (1);
}
