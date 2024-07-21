/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:06:29 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/16 04:55:49 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int    is_space(char *s)
{
    while ((*s >= 9 && *s <= 13) || *s == 32)
        s++;
    if (*s == '\0')
         return (0);
    return (1);    
}

int chr_cmp(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '\0')
        return (1);
    return (0);
}
