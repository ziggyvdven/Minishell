# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 13:45:36 by zvandeven         #+#    #+#              #
#    Updated: 2023/10/02 18:28:04 by zvan-de-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RT	= \033[0m
G	= \033[0;32m
B	= \033[0;34m
R 	= \033[0;31m

define HEADER
███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░
████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░
██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░
██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░
██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝
endef
export HEADER

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Program name
NAME 			= minishell
NAME_BONUS		= minishell_bonus

# Compiler and flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g

# others
RM				= rm -f
MAKE			= make

# Objects 
OBJS_PATH		= objs/
OBJS_B_PATH     = objs_bonus/
OBJS			= $(patsubst $(SRCS_PATH)%.c, $(OBJS_PATH)%.o, $(SRCS_FILES))
OBJS_BONUS		= $(patsubst $(SRCS_B_PATH)%.c, $(OBJS_B_PATH)%.o, $(SRCS_B_FILES))

# Sources
SRCS_PATH		= srcs/
SRCS_B_PATH		= srcs_bonus/
SRCS			= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
SRCS_BONUS		= $(addprefix $(BONUS_PATH), $(SRCS_B_FILES))

# Includes
HEADERS			= -I $(LIBFT)/include 
# RLHEADER		= -I/Users/oroy/.brew/opt/readline/include
RLHEADER		= -I/Users/zvan-de-/.brew/opt/readline/include
# RLHEADER		= -I/usr/local/opt/readline/include
# RLHEADER		= -I/home/linuxbrew/.linuxbrew/opt/readline/include

# library and source files
LIBFT			= ./libs/libft
# READLINE		= -L/Users/oroy/.brew/opt/readline/lib -lreadline
READLINE		= -L/Users/zvan-de-/.brew/opt/readline/lib -lreadline
# READLINE		= -L/usr/local/opt/readline/lib -lreadline
# READLINE		= -L/home/linuxbrew/.linuxbrew/opt/readline/lib -lreadline
LIBS			= $(LIBFT)/libft.a
SRCS_FILES		= $(wildcard $(SRCS_PATH)*.c)
SRCS_B_FILES	= $(wildcard $(SRCS_B_PATH)*.c)

# Progress bar variables
TOTAL 			= $(words $(SRCS_FILES))
CURR  			= 0
PERCENT 		= 0


define update_progress
    $(eval CURR=$(shell echo $$(($(CURR) + 1))))
    $(if $(TOTAL), \
        $(eval PERCENT=$(shell echo $$(($(CURR) * 100 / $(TOTAL))))) \
    )
    @printf "\r\\033[K$(B)Minishell: $(RT) $(PERCENT)%% ["
    @for i in `seq 1 $(PERCENT)`; do \
        printf "$(G)=$(RT)"; \
    done
	@for i in `seq $(PERCENT) 100`; do \
        printf " "; \
    done
    @printf "]"
endef

define print_header
    @echo "$$HEADER"
endef

					
#------------------------------------------------------------------------------#
#                                 RULES                                        #
#------------------------------------------------------------------------------#

all: $(HEAD) libft $(NAME) 

$(NAME): $(OBJS_PATH) $(OBJS) $(LIBFT)
	@$(CC)  $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(HEADERS) $(READLINE)
	@echo "$(G)\n -- $(NAME) made 🐙 --$(RT)"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c 
	@$(CC) $(RLHEADER) $(CFLAGS) -o $@ -c $< 
	$(call update_progress)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

libft:
	@$(call print_header)
	@$(MAKE) -C $(LIBFT)

brew:
	brew --version || curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh

glfw: brew
	brew install glfw

cmake : glfw
	cmake --version | brew install cmake

bonus: $(HEAD) libft $(NAME_BONUS) 

$(NAME_BONUS): $(OBJS_B_PATH) $(OBJS_BONUS) $(LIBFT)
	@$(CC)  $(CFLAGS) -o $@ $(OBJS_BONUS) $(LIBS) $(HEADERS) $(READLINE)
	@echo "$(G)\n -- $(NAME) made 🐙 --$(RT)"

$(OBJS_B_PATH)%.o: $(SRCS_B_PATH)%.c 
	@$(CC) $(RLHEADER) $(CFLAGS) -o $@ -c $< 
	$(call update_progress)

$(OBJS_B_PATH):
	@mkdir -p $(OBJS_B_PATH)

clean:
	@rm -rf $(OBJS) $(OBJS_PATH)
	@rm -rf $(OBJS_BONUS) $(OBJS_B_PATH)
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(R)Files succesfully cleaned 🗑$(RT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY:		all, clean, fclean, re, libmlx

# VALGRIND #

# val: $(NAME)
# 	valgrind --show-reachable=no \
# 	--leak-check=full \
# 	--show-leak-kinds=all \
# 	--track-origins=yes -s \
# 	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	--show-reachable=yes \
	./$(NAME)
