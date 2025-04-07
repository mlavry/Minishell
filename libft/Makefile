# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 18:27:44 by aboutale          #+#    #+#              #
#    Updated: 2025/01/23 18:55:19 by aboutale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_strchr.c ft_strrchr.c ft_strnstr.c \
ft_strdup.c ft_atoi.c ft_toupper.c \
ft_tolower.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memcmp.c ft_strncmp.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_memset.c \
ft_memcpy.c ft_memmove.c ft_memchr.c ft_bzero.c ft_calloc.c \
ft_substr.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c \
ft_strcmp.c ft_strcpy.c ft_strcat.c \


SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \


OBJS := ${SRCS:.c=.o} 
OBJS_BONUS := ${SRCS_BONUS:.c=.o} 

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = cc

all: ${NAME}

${NAME}: ${OBJS} 
	ar rcs ${NAME} ${OBJS}

bonus : ${OBJS} ${OBJS_BONUS}
	ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}
	
.o: .c
	${CC} ${CFLAGS} -c $< -o $@
	@echo Compliling : $<

clean :
	rm -rf ${OBJS} ${OBJS_BONUS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
.PHONY : all clean fclean re bonus 
