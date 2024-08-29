/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:04:07 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/29 20:17:07 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FUN_H
# define LIBFT_FUN_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct _list
{
	char			*token;
	int				type;
	struct _list	*next;
	struct _list	*prev;
}					t_list;

int	    ft_atoi(const char *nptr);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char const *s);
char	**ft_split1(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int	    ft_wordcount(char const *s);
char	*set_word(char *word, char const *s, int *i);
char	*ft_strjoin(char const *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
int	    ft_isdigit(int c);
int     ft_isalpha(int c);
int	    ft_isalnum(int c);
int	    ft_strncmp(const char *s1, const char *s2, size_t len);
int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);



#endif