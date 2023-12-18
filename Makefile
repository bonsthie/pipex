NAME = pipex

CC = clang
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
HSRCS = ./include
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

LIB = libft.a
LIB_DIR = libft

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lft -o $(NAME) -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -MMD -I $(HSRCS) -I $(LIB_DIR) -o $@ -c $< -g

$(LIB):
	$(MAKE) -C $(LIB_DIR)

clean:
	@echo "Cleaning objects"
	@rm -f $(OBJS) $(DEPS)
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@echo "Cleaning executable"
	@rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re $(LIB)
