# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 03:42:44 by bamssaye          #+#    #+#              #
#    Updated: 2024/08/29 23:20:38 by bamssaye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FUN = ft_isalpha.c ft_isdigit.c\
	ft_isalnum.c ft_isascii.c\
	ft_isprint.c ft_strlen.c\
	ft_memset.c ft_bzero.c\
	ft_memcpy.c ft_memmove.c\
	ft_strlcpy.c ft_strlcat.c\
	ft_toupper.c ft_tolower.c\
	ft_strchr.c ft_strrchr.c\
	ft_strncmp.c ft_memchr.c\
	ft_memcmp.c ft_strnstr.c\
	ft_atoi.c ft_calloc.c ft_strdup.c\
	ft_substr.c ft_strjoin.c ft_putnbr_fd.c\
	ft_strtrim.c ft_split.c ft_strcmp.c\
	ft_itoa.c ft_strmapi.c\
	ft_striteri.c ft_putchar_fd.c\
	ft_putstr_fd.c ft_putendl_fd.c\
	ft_lstnew_bonus.c ft_lstadd_back_bonus.c\
	ft_lstlast_bonus.c ft_lstsize_bonus.c\
	realloc.c ft_split2.c ft_split1.c\
 			
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rc
RM = rm -rf
OBGDIR = obj
OBG =  $(addprefix $(OBGDIR)/,  $(notdir $(FUN:.c=.o)))

$(OBGDIR)/%.o:%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBG)
	@$(AR) $(NAME) $(OBG)

clean: 
	@$(RM) $(OBGDIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.SECONDARY: $(OBG)
.PHONY : all clean fclean re 
.SILENT: