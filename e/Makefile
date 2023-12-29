# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fparis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 20:08:41 by fparis            #+#    #+#              #
#    Updated: 2023/12/20 20:52:46 by fparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
HEADER = headers

MAND = mandatory/check_args.c\
	mandatory/ft_split.c\
	mandatory/ft_utils.c\
	mandatory/here_doc.c\
	mandatory/main.c
	
BONUS = bonus/check_args_bonus.c\
	bonus/ft_split_bonus.c\
	bonus/ft_utils_bonus.c\
	bonus/here_doc_bonus.c\
	bonus/main_bonus.c
	
GNL = gnl/get_next_line.c\
	gnl/get_next_line_utils.c
	

OBJ_MAND = $(MAND:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)
OBJ_GNL = $(GNL:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_MAND) $(OBJ_GNL)
	$(CC) $(CFLAGS) $^ -o $(NAME) -I $(HEADER)

bonus: $(OBJ_BONUS) $(OBJ_GNL)
	$(CC) $(CFLAGS) $^ -o $(NAME) -I $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)
	
clean:
	rm -f $(OBJ_MAND) $(OBJ_BONUS) $(OBJ_GNL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
