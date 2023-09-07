# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 13:45:36 by zvandeven         #+#    #+#              #
#    Updated: 2023/09/06 17:15:02 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RT	= \033[0m
G	= \033[0;32m
B	= \033[0;34m

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#
# library name
NAME 			= libft.a

# Compiler and flags
CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror

# others
RM				= rm -f

# Objects 
OBJS_PATH		= objs/
OBJS_DIRS       = $(addprefix $(OBJS_PATH), gnl/ string/ alpha_digit/ memory/ utils/ list/ printf/)
OBJS			= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

# Sources
SRCS_PATH		= srcs/
SRCS			= $(addprefix $(SRCS_PATH), $(SRCS_FILES))

# Includes
INCLUDE_PATH	= includes/
INCS			= -I $(INCLUDE_PATH)
HEADER			= $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))
HEADER_FILES	= libft.h

# source files
SRCS_FILES		= alpha_digit/ft_isalnum.c \
alpha_digit/ft_isalpha.c \
alpha_digit/ft_isascii.c \
alpha_digit/ft_isdigit.c \
alpha_digit/ft_isprint.c \
alpha_digit/ft_tolower.c \
alpha_digit/ft_toupper.c \
gnl/get_next_line.c \
gnl/get_next_line_utils.c \
list/ft_lstadd_back.c \
list/ft_lstadd_front.c \
list/ft_lstdelone.c \
list/ft_lstclear.c \
list/ft_lstiter.c \
list/ft_lstlast.c \
list/ft_lstnew.c \
list/ft_lstsize.c \
memory/ft_bzero.c \
memory/ft_memcpy.c \
memory/ft_memchr.c \
memory/ft_memcmp.c \
memory/ft_memmove.c \
memory/ft_memset.c \
printf/ft_printf.c \
printf/ft_printf_utils.c \
printf/ft_putnbr_base_pf.c \
printf/ft_putnbr_pf.c \
printf/ft_putunsign.c \
printf/ft_printadr.c \
string/ft_split.c \
string/ft_strchr.c \
string/ft_strdup.c \
string/ft_striteri.c \
string/ft_strjoin.c \
string/ft_strlcat.c \
string/ft_strlcpy.c \
string/ft_strlen.c \
string/ft_strmapi.c \
string/ft_strncmp.c \
string/ft_strnstr.c \
string/ft_strrchr.c \
string/ft_strtrim.c \
string/ft_substr.c \
string/ft_substr.c \
string/ft_strisdigit.c \
utils/ft_atoi.c \
utils/ft_atol.c \
utils/ft_calloc.c \
utils/ft_free_ar.c \
utils/ft_free_str.c \
utils/ft_itoa.c \
utils/ft_putchar.c \
utils/ft_putchar_fd.c \
utils/ft_putstr_fd.c \
utils/ft_putendl_fd.c \
utils/ft_putnbr_fd.c \
utils/ft_swap.c \
utils/ft_printmap.c\

# Progress bar variables
TOTAL 			= $(words $(SRCS_FILES))
CURR  			= 0
PERCENT 		= 0

define update_progress
    $(eval CURR=$(shell echo $$(($(CURR) + 1))))
    $(if $(TOTAL), \
        $(eval PERCENT=$(shell echo $$(($(CURR) * 100 / $(TOTAL))))) \
    )
    @printf "\r\\033[K$(B)Libft: $(RT) $(PERCENT)%% ["
    @for i in `seq 1 $(PERCENT)`; do \
        printf "$(G)=$(RT)"; \
    done
	@for i in `seq $(PERCENT) 100`; do \
        printf " "; \
    done
    @printf "]"
endef

#------------------------------------------------------------------------------#
#                                 RULES                                        #
#------------------------------------------------------------------------------#

all: $(NAME) 

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c 
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OBJS_DIRS) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $< -I $(HEADER)
	$(call update_progress)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	
clean:
	@rm -rf $(OBJS) $(OBJS_PATH)
	@rmdir $(OBJS_DIRS) 2> /dev/null || true
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:		all bonus clean fclean re