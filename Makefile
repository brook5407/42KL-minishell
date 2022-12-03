# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 18:05:23 by wricky-t          #+#    #+#              #
#    Updated: 2022/12/03 14:25:44 by wricky-t         ###   ########.fr        #
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
	@make bonus -C $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(RLFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "↻ Compiling $(notdir $<)"

clean:
	@clear
	@make clean -C $(LIBFT)
	@$(RM) $(OBJ_PATH)
	@echo "✗ Removed $(OBJ_PATH)"

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "✗ Removed $(NAME)"

re: fclean all

norm: $(SRCS)
	@clear
	@$(NORM) $(SRCS) $(INCLUDES) $(LIBFT)

.PHONY:
	clean fclean re