DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = philo_bonus


#		./src/process_check.c \

SRC =	./src/monitor.c \
		./src/routine.c \
		./src/check_argv.c \
		./src/free.c \
		./src/utils2.c \
		./src/utils.c \
		./src/main_bonus.c \


OBJ = $(SRC:.c=.o)


CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread
#CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address,leak
# valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q ./philo 4 800 200 200 
CC = gcc
#-no-pie

all: $(NAME) show_progress

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)

#hel: $(NAME)
#	valgrind --tool=helgrind  ./$(NAME) 4 800 210 200 5


#val: $(NAME)
#	valgrind --tool=drd  ./$(NAME) 5 800 200 200

show_progress:
		@for file in $(SRC); do \
			echo "$(GREEN)Compiling $$file "; \
		done; \
		echo "Compiled: 100%$(DEFAULT)"; \

#-c -o $@ $<

clean:
	rm -f  $(NAME)
#rm -f philosopher_bonus

fclean: clean
	rm -f  $(OBJ)
#	rm -f $(OBJB)

re: fclean all

re_bonus: fclean bonus

git:
	git add .
	git commit
	git push

.PHONY: clean fclean re all