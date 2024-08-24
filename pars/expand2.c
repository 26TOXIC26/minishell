/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:24:18 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/24 00:41:37 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_exit_s(char **tab, int i, t_main *mini, char *tmp2)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp4;
	char	*tmp3;

	tmp3 = ft_itoa(mini->exit_status);
	tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
	tmp1 = tmp;
	tmp = ft_strjoin(tmp, tmp3);
	tmp4 = tmp;
	tmp = ft_strjoin(tmp, tmp2 + 2);
	free(tab[i]);
	free(tmp3);
	free(tmp1);
	free(tmp4);
	tab[i] = tmp;
}

char	*ft_strjoinss(char *s1, char *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	size_t	t;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	t = ls1 + ls2 + 1;
	str = ft_calloc(t, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ls1);
	ft_memcpy(str + ls1, s2, ls2);
	free(s1);
	return (str);
}

int	check_quote1(char *str)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			i++;
			while (str[i] != q && str[i])
				i++;
			if (str[i] != q)
				return (0);
		}
		i++;
	}
	return (1);
}
