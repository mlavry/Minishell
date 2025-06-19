NAME = minishell

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I$(SUBDIR) #-fsanitize=address

SRC_EXEC = main.c Exec/pipe.c Exec/builtin.c Exec/builtin2.c Exec/exec.c Exec/export.c Exec/export2.c Exec/export3.c Exec/getpath.c Exec/envp2.c\
Exec/builtin3.c Exec/builtin4.c Exec/exec2.c Exec/exec3.c Exec/envp.c Gnl/get_next_line.c Gnl/get_next_line_utils.c

SRC_PARSING = Parsing/parsing_start.c Parsing/check_quote.c Parsing/tokenize.c Parsing/line_to_token.c Parsing/stock_tokens.c\
Parsing/free.c Utils/utils.c Utils/utils_2.c Parsing/make_commands.c Parsing/token_to_commands.c Parsing/init_struct.c Parsing/exit_code.c\
Parsing/expand.c Utils/utils_3.c Parsing/handle_commands_type.c Parsing/handle_commands.c Utils/signal.c \
Utils/signal_hd.c

SRC = $(SRC_EXEC) $(SRC_PARSING)

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

