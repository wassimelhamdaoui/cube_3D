# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 10:00:27 by waelhamd          #+#    #+#              #
#    Updated: 2022/12/05 21:25:46 by waelhamd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
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