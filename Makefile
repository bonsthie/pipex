NAME = pipex

CC = clang
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
SRC_DIR_BONUS = src_bonus
OBJ_DIR = obj
HSRCS = include
LIBFT = libft/libft.a
HSRCS_BONUS = include_bonus
SRC = pipex.c \
	  manage_file.c \
	  find_cmd.c \
	  free.c \
	  error_msg.c \
	  here_doc.c

SRC_BONUS = $(SRC:%.c=%_bonus.c)

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPULE = \e[0;35m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) libft/libft.a

bonus : libft $(OBJS_BONUS)
	@echo "$(GREEN)Linking $(NAME) bonus...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) libft/libft.a

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I $(HSRCS) -I libft/ -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I $(HSRCS_BONUS) -I libft/ -o $@ -c $< 

$(LIBFT):
	@echo "$(PURPULE)Building libraries...$(NC)"
	@$(MAKE) -C libft -s

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)

lclean:
	@echo "$(RED)Cleaning libraries...$(NC)"
	@$(MAKE) -C libft fclean -s

fclean: clean lclean 
	@echo "$(RED)Cleaning executable $(NAME)...$(NC)"
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean lclean re bonus
