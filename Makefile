# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 18:05:23 by wricky-t          #+#    #+#              #
#    Updated: 2022/12/14 19:09:30 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

NAME		:= minishell

CC			:= gcc

CFLAGS		:= -Wall -Werror -Wextra

CFLAGS		+= -I/usr/local/opt/readline/include

ifeq ($(DB), 1)
	CFLAGS += -fsanitize=address -g3
endif

RLFLAGS		:= -lreadline -L/usr/local/opt/readline/lib

SRC_PATH	:= srcs

OBJ_PATH	:= objs

LIBFT		:= lib42

INCLUDES	:= includes

INCFLAGS	:= -I $(INCLUDES) -I $(LIBFT)

STATLIB		:= $(LIBFT)/*.a

RM			:= rm -rf

NORM		:= norminette

#------------------------------------------------------------------------------#
#   PROGRAM'S SCRS                                                             #
#------------------------------------------------------------------------------#

SRCS		:= minishell.c \
			   init/minishell_init.c \
			   init/environment_init.c \
			   init/signal_init.c \
			   checking/check_dangling.c \
			   lexer/lexer.c \
			   lexer/tokenizer.c \
			   lexer/tokenizer_utils.c \
			   env_utilise.c \
			   cmds/call_cd.c \
			   cmds/call_pwd.c \
			   cmds/call_env.c \
			   cmds/call_exit.c \
			   cmds/call_unset.c \
			   cmds/call_export.c \
			   free/free_env.c \


SRCS		:= $(SRCS:%=$(SRC_PATH)/%)

OBJS		:= $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

#------------------------------------------------------------------------------#
#   STYLING                                                                    #
#------------------------------------------------------------------------------#

GR			:= \033[1;92m

BL			:= \033[1;34m

UBL			:= \033[4;34m

YL			:= \033[1;33m

DF			:= \033[0m

#------------------------------------------------------------------------------#
#   RECIPE                                                                     #
#------------------------------------------------------------------------------#

all: $(NAME)

ifeq ($(DB), 1)
	@echo "🐛 DEBUG MODE 🐛"
endif

$(NAME): $(OBJS)
	@clear
	@echo "$(GR)🚀 Launching $(NAME)...$(DF)"
	@make bonus -C $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(RLFLAGS) $(STATLIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BL)↻ Compiling $(UBL)$(notdir $<)$(DF)"

clean:
	@clear
	@make clean -C $(LIBFT)
	@$(RM) $(OBJ_PATH)
	@echo "$(YL)✗ Removed $(OBJ_PATH)$(DF)"

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(YL)✗ Removed $(NAME)$(DF)"

re: fclean all

norm: $(SRCS)
	@clear
	@$(NORM) $(SRCS) $(INCLUDES) $(LIBFT)

.PHONY:
	clean fclean re