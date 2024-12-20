# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/31 22:41:15 by mait-taj          #+#    #+#              #
#    Updated: 2024/11/04 20:10:22 by mait-taj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c	ft_strchr.c	ft_bzero.c	ft_itoa.c	ft_strmapi.c	ft_putendl_fd.c\
	ft_strdup.c	ft_calloc.c	ft_strlcat.c	ft_strtrim.c	ft_striteri.c\
	ft_strjoin.c	ft_isalnum.c		ft_isalpha.c	ft_split.c	ft_putchar_fd.c\
	ft_strlcpy.c	ft_isascii.c	ft_strlen.c	ft_isdigit.c	ft_strcmp.c	ft_putnbr_fd.c\
	ft_isprint.c	ft_strnstr.c	ft_memchr.c	ft_strrchr.c	ft_memcmp.c	ft_putstr_fd.c\
	ft_substr.c	ft_memcpy.c	ft_tolower.c	ft_memmove.c	ft_toupper.c	ft_memset.c	ft_strncmp.c\

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "[libft archived]"
clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
