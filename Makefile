# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 01:33:05 by amousaid          #+#    #+#              #
#    Updated: 2024/09/07 11:47:51 by amousaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0m
###################
NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
LDFLAGS = -I/usr/local/opt/readline/include
RDFLAG = -L/usr/local/opt/readline/lib -lreadline
RM = rm -rf
LIBFT = ./libft/libft.a
###################
OBGDIR = obj
###################
SRC = main.c \
	bultin/env.c bultin/echo.c bultin/export.c \
	bultin/_builtin.c bultin/cd.c bultin/exit.c \
	bultin/pwd.c bultin/unset.c pars/rm_quotes.c \
	bultin/export_utils.c bultin/set_env.c\
	bultin/expo_env_utlis.c bultin/redir.c\
	execution/check_path.c \
	execution/exec_env.c execution/exec_utils.c\
	execution/exec.c execution/heredoc.c\
	execution/check_err.c execution/redirect.c\
	pars/check.c pars/get_cmd.c pars/command.c pars/redr_expand.c\
	pars/pars.c pars/get_cmd2.c pars/init_cmd.c \
	pars/free_list.c pars/expand.c pars/expand2.c \
	utils/main_clear.c \
	utils/main_shell.c utils/utils.c utils/clear_node.c\
	signal/signal.c signal/signal_ut.c\
####################

OBJ =  $(addprefix $(OBGDIR)/,  $(notdir $(SRC:.c=.o)))

$(OBGDIR)/%.o:%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBGDIR)/%.o:pars/%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBGDIR)/%.o:utils/%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
$(OBGDIR)/%.o:signal/%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
$(OBGDIR)/%.o:bultin/%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBGDIR)/%.o:execution/%.c
	@mkdir -p $(OBGDIR)
	$(CC) $(CFLAGS) -c $< -o $@

####################--no-print-directory
all: $(NAME)

$(LIBFT):
		$(MAKE) --no-print-directory -C ./libft

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(RDFLAG) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)=============================$(NC)"
		@echo "$(GREEN)      Minishell Created      $(NC)"
		@echo "$(GREEN)=============================$(NC)"

clean:
	@$(RM)  -rf $(OBGDIR)
	@$(MAKE) --no-print-directory -C ./libft clean
	@echo "$(RED)=============================$(NC)"
	@echo "$(RED)    Object files removed.    $(NC)"
	@echo "$(RED)=============================$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C ./libft fclean
	@echo "$(RED)=============================$(NC)"
	@echo "$(RED)      Minishell removed      $(NC)"
	@echo "$(RED)=============================$(NC)"


re: fclean all

.SECONDARY: $(OBJ)
.SILENT:
