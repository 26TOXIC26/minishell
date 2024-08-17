/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:24:18 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/17 21:50:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_exit_s(char **tab, int i, t_main *mini, char *tmp2)
{
	char	*tmp;

	tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
	tmp = ft_strjoin(tmp, ft_itoa(mini->exit_status));
	tmp = ft_strjoin(tmp, tmp2 + 2);
	free(tab[i]);
	tab[i] = tmp;
}
