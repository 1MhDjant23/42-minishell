NAME = minishell

SRC = exec/utils.c exec/minishell.c exec/builtins.c    exec/execute.c\
    parsers/Lexer_new.c parsers/lexer_utils.c parsers/parse.c parsers/utilsp.c\
    parsers/main.c    parsers/init_y.c    parsers/syntax.c    parsers/syntax_error.c    parsers/cut.c\
	parsers/lexer_ut.c	parsers/parse_add.c	parsers/parse_env.c	parsers/parse_utils.c	parsers/parse_free.c\
	parsers/parse_cut.c\
    exec/export.c exec/utils1.c exec/utils_v1.c exec/cleanner.c exec/error_handling.c\
    exec/exec_utils.c exec/ft_echo.c exec/ft_cd.c exec/execut_v1.c exec/pipe_handling.c\
    exec/ft_redirection.c exec/herdoc.c exec/handl_signal.c exec/ft_pwd.c exec/ft_exit.c\
	exec/execve_func.c exec/ft_env.c exec/herdoc_utils.c exec/herdoc_utils2.c exec/ft_unset.c\
	exec/step_one_to_exec.c\

LIBFT = libft/libft.a

H_LIBFT = libft/libft.h

HEADER = minishell.h

HEADER2 = exec/structs.h

CC = cc

OBJ = $(addprefix obj/, $(SRC:.c=.o))

INRL = -I/Users/mait-taj/.brew/include/

LNRL= -lreadline -L/Users/mait-taj/.brew/lib/

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) logo

obj/%.o: %.c $(HEADER) $(HEADER2) $(H_LIBFT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INRL) -c $< -o $@

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIBFT) ${INRL} ${LNRL} $(SRC)   -o $(NAME)
	@echo "\033[0;34m[the project compiled successfully]\033[0m\n"	
logo:
	@printf "\033[0;36m"
	@printf "\n ▄▄▄▄  ▄ ▄▄▄▄  ▄  ▄▄▄ ▐▌   ▗▞▀▚▖█ █ "
	@printf "\n █ █ █ ▄ █   █ ▄ ▀▄▄  ▐▌   ▐▛▀▀▘█ █ "
	@printf "\n █   █ █ █   █ █ ▄▄▄▀ ▐▛▀▚▖▝▚▄▄▖█ █ "
	@printf "\n       █       █      ▐▌ ▐▌     █ █ "
	@printf "\033[0m \n"

clean:
	@make clean -C libft/
	@rm -rf obj/exec obj/parsers

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
