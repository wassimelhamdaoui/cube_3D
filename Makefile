# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 10:00:27 by waelhamd          #+#    #+#              #
#    Updated: 2023/01/10 21:16:15 by waelhamd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parsing.c get_next_line.c get_next_line_utils.c utils.c utils1.c utils2.c
OBJ = $(SRC:.c=.o)

CFLAGS =  -Imlx
CC = cc

NAME = cub3d

%.o: %.c
	$(CC) $(CFLAGS) -c $<

all : $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
		rm -rf $(OBJ)
fclean : clean
		rm -rf $(NAME)
re : fclean all