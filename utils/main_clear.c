/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:38:19 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 23:44:09 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	arry_c(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void _clearmini(t_main *m)
{
	
	free(m->mini.line);
	arry_c(m->mini.env);
	arry_c(m->bultin);
	//ft_lstclear_collec(&m->cmd, del_collec);
	rl_clear_history();
	free(m);
	exit(0);
}


