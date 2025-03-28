#  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
#  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀                𓐓  Makefile 𓐔           
#  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
#  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
#  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
#  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
#  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 16:57:09 by mait-taj
#  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 16:57:16 by mait-taj
#  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
#  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
#  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
#  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
#  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              


#===============| < Colors: > |=================#

# Reset
RESET = \033[0m
# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
# Bold
BBLACK = \033[1;30m
BRED = \033[1;31m
BGREEN = \033[1;32m
BBLUE = \033[1;34m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BWHITE = \033[1;37m
# Underline
UBLACK = \033[4;30m

#===============| < CC:Compiler: > |=================#
CC = cc

CFLAGS = -Wall -Wextra -Werror

#===============| < NAME: > |=================#

NAME = minishell

#===============| < Sources: > |=================#

SRC = $(shell find exec parsers -name '*.c')

INCLUDE = $(shell find . -name '*.h')

LIBFT = libft/libft.a

INRL = -I/Users/mait-taj/.brew/include/

LNRL= -lreadline -L/Users/mait-taj/.brew/lib/

OBJ = $(addprefix obj/, $(SRC:.c=.o))


#===============| < Rules: > |=================#

all: logo signature1 $(NAME) signature

obj/%.o: %.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INRL) -c $< -o $@

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIBFT) ${INRL} ${LNRL} $(SRC) -o $(NAME)
	@echo "$(BBLUE)🚀 [The project compiled successfully] 🎉$(RES)\n"	

clean:
	@make clean -C libft/
	@rm -rf obj/exec obj/parsers
	@printf "$(RED)🧹 [ all objects files cleaned ] 🗑️🧽$(RESET)\n"

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@printf "$(BRED)🧹 [ The project cleaned successfully ] 🎉$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

#===============| < Logo && signature: > |=================#

logo:
	@printf "$(BGREEN)"
	@printf "\n ▄▄▄▄  ▄ ▄▄▄▄  ▄  ▄▄▄ ▐▌   ▗▞▀▚▖█ █ "
	@printf "\n █ █ █ ▄ █   █ ▄ ▀▄▄  ▐▌   ▐▛▀▀▘█ █ "
	@printf "\n █   █ █ █   █ █ ▄▄▄▀ ▐▛▀▚▖▝▚▄▄▖█ █ "
	@printf "\n       █       █      ▐▌ ▐▌     █ █ $(RESET)\n"

signature:
	@printf "\n$(BBLACK)©️ All rights reserved to $(UBLACK) mait-taj $(RESET) $(BBLACK)&&$(UBLACK) ysouhail$(RESET)\n"

signature1:
	@printf "\n$(BLACK)🛠️🔧powered by: $(BBLUE)mait-taj && ysouhail$(RESET)\n"
#===============| < END: > |=================#