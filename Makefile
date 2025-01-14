NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS =	main.c \
		monitor.c \
		utils.c \
		routine_utils.c \
		validations.c \
		eating_cases.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)
	@echo "															"	
	@echo "															"	
	@echo "															"	
	@echo "$(G)██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗$(RESET)	"
	@echo "$(G)██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝$(RESET)	"
	@echo "$(G)██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗$(RESET)	"
	@echo "$(G)██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║$(RESET)	"
	@echo "$(G)██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║$(RESET)	"
	@echo "$(G)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝$(RESET)	"
	@echo "					 										"	

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re