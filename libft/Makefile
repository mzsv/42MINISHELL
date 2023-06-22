# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:26:23 by amitcul           #+#    #+#              #
#    Updated: 2023/06/05 20:52:19 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
INCLUDE		=	includes/
SRC_DIR 	=	src/
OBJ_DIR		=	obj/
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -I
AR			=	ar rcs

OBJF		=	.cache_exists

LIB_DIR		=
LIB_SRC		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strtrim ft_substr \
				ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize \
				ft_atoi ft_itoa ft_tolower ft_toupper \
				ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
				ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset ft_memcpy \
				ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
				get_next_line get_next_line_utils ft_iswhitespace

SRC_FILES+=$(addprefix $(LIB_DIR),$(LIB_SRC))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(LIB_DIR)
	@touch $(OBJF)

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(OBJF)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
