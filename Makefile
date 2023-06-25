# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 11:02:30 by amitcul           #+#    #+#              #
#    Updated: 2023/06/25 12:26:01 by amitcul          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	cc -fPIE
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
RM		=	rm -rf
OS		:= 	$(shell uname)

LIBDIR = ./libft

ifeq ($(OS), Darwin)
	LIB = $(LIBDIR)/libft.a -lreadline -L/Users/alexmitcul/.brew/opt/readline/lib
else
	LIB = $(LIBDIR)/libft.a -lreadline -L/Users/alexmitcul/.brew/opt/readline/lib
endif

INCLUDES = ./includes/

ifeq ($(OS), Darwin)
	INCLUDES_LIB = ./libft/includes/ -I/Users/alexmitcul/.brew/opt/readline/include/
else
	INCLUDES_LIB = ./libft/includes/ -I/Users/alexmitcul/.brew/opt/readline/include/
endif

HEADER += $(INCLUDES)minishell.h
HEADER += $(INCLUDES)utils.h
HEADER += $(INCLUDES)lexer.h
HEADER += $(INCLUDES)parser.h
HEADER += $(INCLUDES)expander.h

LIB_TERMCAP = -lreadline

SRCS += main.c

# Error files
SRCS += error.c

# Lexer source files
SRCS += quotes.c tokens.c lexer_utils.c

# Parser source files
SRCS += parser.c command.c parser_utils.c redirections.c

# Expander files
SRCS += expander.c double_quotes.c expander_utils.c expanders.c

# Utils source files
SRCS += doubly_linked_list_utils.c env_list.c count_symbol_in_string.c \
		main_utils.c

# Builtins source files
SRCS += unset.c env.c echo.c export.c export_utils.c pwd.c exit.c cd.c \
		sig_config.c env_list_utils.c \

# Executer source files
SRCS += commands.c exec_builtin.c exec_utils.c executor.c fds.c heredoc.c \
		heredoc_signals.c prompt.c redirector.c subshells.c \

OBJ_DIR = ./obj/

vpath %.c src/

vpath %.c src/error/

vpath %.c src/lexer/
vpath %.c src/parser/
vpath %.c src/expander/
vpath %.c src/executor/

vpath %.c src/utils/
vpath %.c src/builtin/unset
vpath %.c src/builtin/env
vpath %.c src/builtin/echo
vpath %.c src/builtin/export
vpath %.c src/builtin/pwd
vpath %.c src/builtin/exit
vpath %.c src/builtin/cd
vpath %.c src/builtin/builtin_utils
vpath %.c src/builtin/

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -I $(INCLUDES_LIB) -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) $(LIB) -L./libft -lft -o $@

$(OBJ_DIR):
	mkdir $@

$(LIB):
	$(MAKE) -C $(LIBDIR)

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)
	$(RM) -R $(OBJ_DIR)

clean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)

re : fclean
	$(MAKE)
