# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 18:05:23 by wricky-t          #+#    #+#              #
#    Updated: 2022/12/02 13:00:04 by wricky-t         ###   ########.fr        #
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

LIBFT		:=

INCLUDES	:= includes

RM			:= rm -rf

NORM		:= norminette

#------------------------------------------------------------------------------#
#   PROGRAM'S SCRS                                                             #
#------------------------------------------------------------------------------#

SRCS		:= minishell.c

SRCS		:= $(SRCS:%=$(SRC_PATH)/%)

OBJS		:= $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

#------------------------------------------------------------------------------#
#   RECIPE                                                                     #
#------------------------------------------------------------------------------#

all: $(NAME)

ifeq ($(DB), 1)
	@echo "🐛 DEBUG MODE 🐛"
endif

$(NAME): $(OBJS)
	@echo "↻ Creating $(NAME)..."
	@$(CC) $(CFLAGS) $^ $(RLFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "↻ Compiling $(notdir $<)"

clean:
	@clear
	@$(RM) $(OBJ_PATH)
	@echo "✗ Removed $(OBJ_PATH)"

fclean: clean
	@$(RM) $(NAME)
	@echo "✗ Removed $(NAME)"

re: fclean all

norm: $(SRCS)
	@clear
	@$(NORM) $(SRCS) $(INCLUDES) $(LIBFT)

.PHONY:
	clean fclean re