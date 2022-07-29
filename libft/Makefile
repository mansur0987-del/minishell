# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 21:57:47 by nmordeka          #+#    #+#              #
#    Updated: 2022/03/15 19:09:23 by armaxima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	libft.a
#
SRCS =	ft_isalpha.c	ft_isdigit.c		ft_isalnum.c \
		ft_isascii.c	ft_isprint.c		ft_strlen.c \
		ft_memset.c		ft_bzero.c			ft_memcpy.c \
		ft_memmove.c	ft_strlcpy.c		ft_strlcat.c \
		ft_toupper.c	ft_tolower.c		ft_strchr.c \
		ft_strrchr.c	ft_strncmp.c		ft_memchr.c \
		ft_memcmp.c		ft_strnstr.c		ft_atoi.c \
		ft_calloc.c		ft_strdup.c			ft_substr.c \
		ft_strjoin.c	ft_strtrim.c		ft_split.c \
		ft_itoa.c		ft_strmapi.c		ft_striteri.c \
		ft_putchar_fd.c	ft_putnchar_fd.c 	get_next_line.c \
		ft_putstr_fd.c	ft_putendl_fd.c		ft_putnbr_fd.c \
		ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c \
		ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c \
		ft_lstclear.c	ft_lstiter.c		ft_lstmap.c \
		ft_dlstnew.c	ft_dlstadd_front.c	ft_dlstadd_back.c \
		ft_dlstsize.c	ft_dlstdelone.c 	ft_dlstclear.c \
		ft_dlstiter.c	ft_dlstmap.c
#
HEADER	=	libft.h
OBJ	=	$(patsubst %.c, %.o, $(SRCS))
#
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I.
RM 	=	rm -f
#
.PHONY	:	all clean fclean re
#
all	:		$(NAME)
#
$(NAME)	:	$(OBJ) $(HEADER)
	@ar rcs $(NAME) $?
#
%.o 	: 	%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

#
#bonus	:	all
#	make OBJ="$(OBJ_B)" all
#
clean	:
	@$(RM) $(OBJ)
	@echo "object files $(NAME) clean"
#
fclean	:	clean
	@$(RM) $(NAME)
	@echo "$(NAME) clean"
#
re	:	fclean all
#
