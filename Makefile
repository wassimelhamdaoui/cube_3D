# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 10:00:27 by waelhamd          #+#    #+#              #
#    Updated: 2023/01/17 21:47:28 by waelhamd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parsing.c get_next_line.c get_next_line_utils.c utils.c utils1.c utils2.c check_xpm_fc.c clone_from_file.c check_map.c parsing_init.c
OBJ = $(SRC:.c=.o)

CFLAGS =  -Imlx
CC = cc

NAME = cub3d

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $<

all : $(NAME)

$(NAME): $(OBJ) cub3d.h
		$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
		rm -rf $(OBJ)
fclean : clean
		rm -rf $(NAME)
re : fclean all