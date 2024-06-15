/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:00:58 by amousaid          #+#    #+#             */
/*   Updated: 2024/06/15 03:07:32 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    new_ptr = malloc(size);
    if (!new_ptr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);
    return (new_ptr);
}