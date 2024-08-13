# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 01:33:05 by amousaid          #+#    #+#              #
#    Updated: 2024/08/13 14:30:31 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0m
###################
NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RM = rm -rf
LIBFT = ./libft/libft.a
###################
OBGDIR = obj
SRC_DIRS = pars utils
###################
SRC = 	minishell.c bultin/env.c signal/signal.c\
		pars/pars.c pars/check.c\
		pars/get_cmd.c pars/command.c pars/get_cmd2.c\
		utils/utils.c pars/init_cmd.c utils/g_collector.c utils/g_collector2.c\
		pars/free_list.c pars/expand.c pars/expand2.c rm_quotes.c\
		bultin/echo.c bultin/pwd.c bultin/unset.c\
		bultin/export.c bultin/cd.c\
		bultin/_builtin.c bultin/exit.c\

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
$(OBGDIR)/%.o:signal/%.c
	@mkdir -p $(OBGDIR)
	@$(CC) $(CFLAGS) -I/usr/local/opt/readline/include -c $< -o $@ 
$(OBGDIR)/%.o:bultin/%.c
	@mkdir -p $(OBGDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

####################
all: $(NAME)

$(LIBFT):
		$(MAKE) --no-print-directory -C ./libft

$(NAME): $(OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -lreadline $(OBJ) $(LIBFT) -o $(NAME) 
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