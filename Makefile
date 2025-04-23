# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutale <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:01:52 by aboutale          #+#    #+#              #
#    Updated: 2025/03/24 18:01:53 by aboutale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c envp.c builtin.c builtin2.c export.c export2.c getpath.c exec.c 

OBJS = $(SRCS:.c=.o)

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 -lreadline

CC = cc

LIBFT = libft/libft.a

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g3 -c $< -o $@ 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -Llibft -lft -lreadline -o $(NAME) $(CFLAGS)

all: $(NAME)

$(LIBFT) :
	make all -C libft
clean:
	rm -rf $(OBJS) 
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

