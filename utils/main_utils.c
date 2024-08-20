/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:37:30 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 14:39:21 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_main	*_initminish(char **env)
{
	t_main	*minish;

	minish = _malloc(sizeof(t_main));
	minish->cmd = NULL;
	minish->command = NULL;
	minish->exit_status = 0;
	minish->bultin = i_bultin();
	minish->env = set_envc(env);
	return (minish);
}