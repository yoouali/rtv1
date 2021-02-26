# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/25 10:38:14 by ayagoumi          #+#    #+#              #
#    Updated: 2021/02/25 18:08:49 by yoouali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = rtv1

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB = libft/libft.a 

SDLF = -I SDL/SDL2.framework/Headers   

INC = inc/rtv1.h libft/libft.h 

SRC = srcs/main.c srcs/window/sdl_init.c srcs/events/events.c srcs/vec_utility_functions/functions.c  srcs/xml/check_file.c srcs/xml/color.c srcs/xml/data.c srcs/xml/data2.c srcs/xml/last.c srcs/xml/leak.c srcs/xml/load.c srcs/xml/object.c srcs/xml/rule.c srcs/xml/xml.c srcs/raycast/raycast.c

FRAM = -lmlx -framework OpenGL -framework AppKit -framework OpenCL  -framework SDL2 -F ./SDL/ -framework SDL2_mixer -F ./SDL  -framework SDL2_image -F ./SDL -framework SDL2_ttf -F ./SDL -rpath @loader_path/SDL -lz 

OBJ = $(SRC:.c=.o) 

F_OBJ = ./OBJ

all: $(NAME) 
$(NAME):$(OBJ)$(INC)
		@echo "\033[2;36m"
	    @make -C ./mlx  2> /dev/null || true
		@make -C ./libft  2> /dev/null || true
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(FRAM)  $(SDLF) -o $(NAME)
		@echo "Wolf_3d: executable file is ready"
		@echo "\033[0m"
clean:
		@echo "\033[2;32m"
		@make clean -C ./mlx  2> /dev/null || true
		@make clean -C ./libft  2> /dev/null || true
		@rm -rf $(OBJ)   2> /dev/null || true
		@echo "Wolf_3d: all resources deleted"
		@echo "\033[0m"
fclean: clean 
		@echo "\033[2;34m"
		@rm -f $(NAME)  2> /dev/null || true
		@make fclean -C ./libft  2> /dev/null || true
		@make fclean -C ./mlx  2> /dev/null || true
		@echo "Wolf_3d: all resources deleted"
		@echo "\033[0m"
re: fclean all