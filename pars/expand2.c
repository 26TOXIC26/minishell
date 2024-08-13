/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:24:18 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/13 15:30:11 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_exit_s(char **tab, int i, t_main *mini, char *tmp2)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
	tmp = ft_strjoin(tmp, ft_itoa(mini->exit_status));
	tmp = ft_strjoin(tmp, tmp2 + 2);
	free(tab[i]);
	tab[i] = tmp;
}
