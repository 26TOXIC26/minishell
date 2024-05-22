/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:11:56 by bamssaye          #+#    #+#             */
/*   Updated: 2023/11/25 03:00:38 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	d;
	size_t	s;

	s = ft_strlen(src);
	if (!dest && !n)
		return (s);
	d = ft_strlen(dest);
	if (d >= n)
		return (n + s);
	if (s < n - d)
		ft_memcpy(dest + d, src, s + 1);
	else
	{
		ft_memcpy(dest + d, src, n - d - 1);
		dest[n - 1] = '\0';
	}
	return (s + d);
}
// #include <stdio.h>
// #include <bsd/string.h>
// int main()
// {
// 	char d[42] = "hello";
// 	printf("%lu",ft_strlcat(NULL,NULL,0));
// }