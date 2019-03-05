NAME			=	ft_ls

# Sources
SRC				=	srcs/arg.c srcs/device.c \
					srcs/error.c srcs/fill.c \
					srcs/fill_t_l.c srcs/ft_ls.c \
					srcs/full_fill.c srcs/full_fill2.c \
					srcs/misc.c srcs/print.c \
					srcs/print2.c srcs/print3.c \
					srcs/sorting.c srcs/sorting2.c

LIBFT_FOLDER	=	libft
LIBFT			=	$(LIBFT_FOLDER)/libft.a

# Compilation
CXX				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -Ofast
INCLUDES		=	-I includes -I $(LIBFT_FOLDER)/includes

# Debug
DEBUGFLAG		=	-Og -g

# Linking
OBJ				=	$(SRC:.c=.o)

# Colors
GREEN			=	\033[32m
RESET			=	\033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@printf "$(GREEN)[cc]$(RESET): done\n"
	@printf "$(GREEN)[ld]$(RESET): $(NAME)\n"
	@$(CXX) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBFT)

.c.o: $(SRC)
	@printf "$(GREEN)[cc]$(RESET): $< -> $@\n"
	@printf "\e[1A"
	@gcc -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@printf "\e[0K"

debug: $(LIBFT) $(OBJ)
	@printf "$(GREEN)[cc]$(RESET): done\n"
	@printf "$(GREEN)[ld]$(RESET): $(NAME)\n"
	@$(CXX) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBFT)

$(LIBFT):
	@printf "\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft all\n";
	@make -C libft
	@printf "\e[1A\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft all done\n";

libft-clean:
	@printf "\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft clean\n";
	@make -C $(LIBFT_FOLDER) clean >/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft clean done\n";

libft-fclean:
	@printf "\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft fclean\n";
	@make -C $(LIBFT_FOLDER) fclean >/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft fclean done\n";

libft-re:
	@printf "\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft re\n";
	@make -C $(LIBFT_FOLDER) re
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft re done\n";

clean: libft-clean
	@printf "\e[0K"
	@printf "$(GREEN)[rm]$(RESET): cleaned object files\n"
	@rm -rf $(OBJ)

fclean: clean libft-fclean
	@printf "\e[0K"
	@printf "$(GREEN)[rm]$(RESET): cleaned binary file\n"
	@rm -rf $(NAME)

separator:
	@printf "\n"

re: fclean separator $(LIBFT) all

.PHONY: separator libft-clean libft-fclean libft-re clean fclean re
