# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 01:33:05 by amousaid          #+#    #+#              #
#    Updated: 2024/07/16 05:47:49 by abdelilah        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0m
###################
NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
LIBFT = ./libft/libft.a
###################
OBGDIR = obj
SRC_DIRS = pars utils
###################
SRC = 	minishell.c env.c signal.c\
		pars/pars.c pars/check.c\
		pars/get_cmd.c pars/command.c\
		utils/utils.c pars/init_cmd.c\
		pars/free_list.c pars/symbol.c\

####################
OBJ =  $(addprefix $(OBGDIR)/,  $(notdir $(SRC:.c=.o)))

$(OBGDIR)/%.o:%.c
	@mkdir -p $(OBGDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBGDIR)/%.o:pars/%.c
	@mkdir -p $(OBGDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBGDIR)/%.o:utils/%.c
	@mkdir -p $(OBGDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

####################
all: $(NAME)

$(LIBFT):
		$(MAKE) --no-print-directory -C ./libft

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
		@echo "$(GREEN)=============================$(NC)"
		@echo "$(GREEN)      Minishell Created      $(NC)"
		@echo "$(GREEN)=============================$(NC)"

clean:
	$(RM)  -rf $(OBGDIR)
	$(MAKE) --no-print-directory -C ./libft clean
	@echo "$(RED)=============================$(NC)"
	@echo "$(RED)    Object files removed.    $(NC)"
	@echo "$(RED)=============================$(NC)"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) --no-print-directory -C ./libft fclean
	@echo "$(RED)=============================$(NC)"
	@echo "$(RED)      Minishell removed      $(NC)"
	@echo "$(RED)=============================$(NC)"

	
re: fclean all

.SECONDARY: $(OBJ)

.SILENT: