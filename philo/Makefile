# Color Aliases

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = philo

NAMEB = bonus

SRC =	./src/monitoring.c \
		./src/routine.c \
		./src/check_argv.c \
		./src/tools2.c \
		./src/tools.c \
		./src/free.c \
		./src/main.c \

SRCB =

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=thread
#CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address,leak
CC = gcc
#-no-pie

all: $(NAME) show_progress

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)

hel: $(NAME)
	valgrind --tool=helgrind  ./$(NAME) 4 800 210 200 5


#val: $(NAME)
#	valgrind --tool=drd  ./$(NAME) 5 800 200 200

show_progress:
		@for file in $(SRC); do \
			echo "$(GREEN)Compiling $$file "; \
		done; \
		echo "Compiled: 100%$(DEFAULT)"; \

#-c -o $@ $<

bonus:

$(NAMEB): $(OBJB) show_progress2
	$(CC) $(CFLAGS) $(OBJB) -o philosopher_bonus

show_progress2:
		@for file in $(SRCB); do \
			echo "$(GREEN)Compiling $$file "; \
		done; \
		echo "Compiled: 100%$(DEFAULT)"; \

clean:
	rm -f  $(NAME)
#	rm -f $(NAMEB)
#rm -f philosopher_bonus

fclean: clean
	rm -f  $(OBJ)
#	rm -f $(OBJB)
#	rm -f philosopher_bonus

re: fclean all

re_bonus: fclean bonus

git:
	git add .
	git commit
	git push

.PHONY: clean fclean re all