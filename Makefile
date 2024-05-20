# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 01:33:05 by amousaid          #+#    #+#              #
#    Updated: 2024/05/20 01:34:24 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM =rm -rf
SRC = minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Building...     ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

clean:
	$(RM) $(OBJ)
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Cleaning...     ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

fclean: clean
	$(RM) $(NAME)
	@echo " ┏━━━━━━━━━━━━━━━━━━━━━━┓"
	@echo "━┃      Full clean...   ┃━"
	@echo " ┗━━━━━━━━━━━━━━━━━━━━━━┛"

re: fclean all

.SILENT: