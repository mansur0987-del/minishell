# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 12:33:43 by armaxima          #+#    #+#              #
#    Updated: 2022/03/30 15:13:09 by nmordeka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft.a
LIBFT_PATH	= ./libft
NAME = minishell

SRC = src/main/main.c \
	src/init/ft_init_mshell.c	src/init/ft_init_base.c \
	src/read/ft_read_line.c		src/read/ft_quotes.c	src/read/ft_line_clear.c \
	src/read/ft_put_var.c \
	src/checking/ft_check_comand.c			src/checking/ft_check_comand_1.c \
	src/checking/ft_utils.c		src/checking/ft_check_params.c \
	src/error/ft_puterror.c 	src/error/ft_memory_err.c	src/error/file_errors.c \
	src/put_comand/put_comand.c src/free/free_proc.c \
	src/free/ft_free_read.c 	src/free/free_tools.c		src/free/ft_free_com.c\
	src/builtin/other_cmd.c		src/builtin/ft_pwd.c		src/builtin/ft_cd.c  \
	src/builtin/ft_env.c		src/builtin/ft_export.c		src/builtin/refresh.c \
	src/builtin/ft_exit.c		src/builtin/ft_unset.c		src/builtin/ft_echo.c \
	src/tools/fd.c				src/tools/ft_lst_utils.c \
	src/tools/ft_lstcopy.c		src/tools/ft_lstsort.c		src/tools/ft_atoull.c \
	src/tools/tools.c			src/tools/env_tools.c 		src/tools/ft_extract_env.c \
	src/process/ft_process.c 	src/process/ft_pipe.c		src/process/ft_exit_ret.c  \
	src/process/redirect.c		src/process/ft_com.c 		src/process/ft_reading.c \
	src/process/ft_exec.c		src/process/handle_signals.c \

OBJ	=	$(patsubst %.c, %.o, $(SRC))

HEADERS = includes/
CC		=	gcc
CFLAGS	= -Wall -Wextra -Werror
RM 		=	rm -f
READLINE_LIB = ./readline/8.1.2/lib
READLINE_INC = ./readline/8.1.2/include

%.o : %.c $(HEADERS)*.h
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERS) -I$(READLINE_INC)

all: $(NAME)

$(NAME): $(LIBFT_PATH)/$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -L$(LIBFT_PATH) -lreadline -lft -L$(READLINE_LIB) -I$(READLINE_INC)
	@echo "object files $(NAME) created"
	@echo "$(NAME) created"

$(LIBFT_PATH)/$(LIBFT): force
	@$(MAKE) -C $(LIBFT_PATH)/
	@echo "libft created"

force : ;

clean:
	@make -C $(LIBFT_PATH)/ clean
	@$(RM) $(OBJ)
	@echo "object files clean"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_PATH)/*.a
	@$(RM) tmp.tpm
	@echo "libft clean"
	@echo "$(NAME) clean"

re: fclean all

.PHONY: all clean fclean re force
