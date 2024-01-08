NAME = pipex

CC = clang
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
HSRCS = include
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m 


LIBRARIES = LIBFT FT_PRINTF

LIBFT_FLAG = -lft
LIBFT_DIR = libft
LIBFT_INCLUDE = .

LIB = $(foreach lib,$(LIBRARIES),-L $($(lib)_DIR) $($(lib)_FLAG))
LIB_DIR = $(foreach lib,$(LIBRARIES),-I $($(lib)_DIR)/$($(lib)_INCLUDE))

all: libraries $(NAME)


$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(DEBUG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I $(HSRCS) $(LIB_DIR) -o $@ -c $< $(DEBUG)

libraries:
	@echo "$(YELLOW)Building libraries...$(NC)"
	$(foreach lib,$(LIBRARIES), $(MAKE) -C $($(lib)_DIR) -j;)

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)

lclean:
	@echo "$(RED)Cleaning libraries...$(NC)"
	@$(foreach lib,$(LIBRARIES),$(MAKE) -C $($(lib)_DIR) clean;)

fclean: clean lclean
	@echo "$(RED)Cleaning executable $(NAME)...$(NC)"
	@rm -f $(NAME)
	@$(foreach lib,$(LIBRARIES),$(MAKE) -C $($(lib)_DIR) fclean;)

re : fclean all

.PHONY: all clean fclean lclean re libraries
