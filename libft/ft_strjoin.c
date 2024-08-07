/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:14:59 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/07 07:17:31 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char *s2)
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
	free(s2);
	return (str);
}
