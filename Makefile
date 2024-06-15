# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pc <pc@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 01:33:05 by amousaid          #+#    #+#              #
#    Updated: 2024/06/15 03:21:36 by pc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
SRC = minishell.c\
		env.c\
		pars/pars.c\
		pars/check.c\
		pars/get_cmd.c\
		pars/command.c\
		utils/utils.c\

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
		$(MAKE) --no-print-directory -C ./libft


$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Building...     ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

clean:
	$(RM) $(OBJ)
	$(MAKE) --no-print-directory -C ./libft clean
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Cleaning...     ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) --no-print-directory -C ./libft fclean
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Full clean...   ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

re: fclean all

.SECONDARY: $(OBJ)

.SILENT: