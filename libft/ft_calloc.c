/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 04:36:02 by bamssaye          #+#    #+#             */
/*   Updated: 2023/11/25 01:36:38 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	s;

	s = nmemb * size;
	if (size && (s / size) != nmemb)
		return (NULL);
	p = malloc(s);
	if (!p)
		return (NULL);
	ft_memset(p, 0, s);
	return (p);
}
