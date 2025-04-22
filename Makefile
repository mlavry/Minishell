NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(SUBDIR)

SRC = main.c Parsing/parsing_start.c Parsing/check_quote.c Parsing/tokenize.c Parsing/line_to_token.c Parsing/stock_tokens.c\
envp.c utils.c

OBJ = $(SRC:.c=.o)
SUBDIR = Libft

RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
NC		:= \033[0m

all: $(NAME)

$(NAME): $(SUBDIR)/libft.a $(OBJ)
	$(CC)	$(CFLAGS)	$(OBJ)	$(SUBDIR)/libft.a -lreadline -o	$(NAME)
	@echo "$(GREEN)FINISHED COMPILING $(NAME)!$(NC)"

$(SUBDIR)/libft.a:
	$(MAKE) -C $(SUBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(SUBDIR) clean
	@echo "$(YELLOW)OBJECTS FILES DELETED!$(NC)"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(SUBDIR) fclean
	@echo "$(RED)ALL FILES CLEAN!$(NC)"

re: fclean all

.PHONY: all clean fclean re
