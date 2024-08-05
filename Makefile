NAME = philo
CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror -g3 #-fsanitize=thread
HEADER = ./includes

SRC = ./philosopher.c ./utils.c ./parsing.c ./routine.c ./routine_utils.c ./visor_routine.c
OBJ = $(SRC:.c=.o)

GREEN    = \033[38;5;76m
RED        = \033[38;5;160m
YELLOW    = \033[38;5;226m  
ORANGE    = \033[38;5;202m
PURPLE    = \033[38;5;213m
LBLUE    = \033[38;5;51m
BLUE    = \033[38;5;117m
INDI    = \033[38;5;99m
RESET    = \033[00m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(HEADER) -o $@ $(OBJ)
	@printf "$(YELLOW)\n"
	@echo "⠀⠀⠀⠰⣌⣘⠃⢂⠁⠀⠐⠁⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢌⠘⣿⣦⣠"
	@echo "⠀⠀⠀⢠⡾⣷⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢿⣿⣏"
	@echo "⠀⠀⠀⢈⣷⡔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣆"
	@echo "⠀⠒⠾⢿⡭⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣿"
	@echo "⠀⠀⡐⢡⣣⠀⠀⠀⠀⣇⢻⢆⠃⠀⠀⠀⠀⡤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏"
	@echo "⠀⠀⠀⠸⢻⠀⠀⠀⠄⠀⠘⢄⠐⠅⣀⣥⣠⣼⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⢜⣀"
	@echo "⠀⠀⠀⣀⢆⠀⠀⠀⣄⢀⡠⡐⣶⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⢀⢫⡁"
	@echo "⠀⠀⠀⠀⠈⠀⠀⠘⢸⣿⣇⠈⠉⠉⣹⣿⣿⣿⡿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠑"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣷⠠⠾⢟⣛⡋⠉⢰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣆⠉⠁⣀⣀⠀⣾⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢗"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣇⠬⠭⢑⡴⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣏⠩⢉⣴⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠻⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
 
.PHONY: all clean fclean re