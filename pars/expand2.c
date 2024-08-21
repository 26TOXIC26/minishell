/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:24:18 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/21 00:49:14 by codespace        ###   ########.fr       */
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
