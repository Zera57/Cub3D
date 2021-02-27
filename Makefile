# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/27 15:14:26 by hapryl            #+#    #+#              #
#    Updated: 2021/02/27 16:31:10 by hapryl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
INCLUDES = -I./cub3d.h -I./gnl/get_next_line.h -I$(LX_DIR) -I$(LFT_DIR)
FOLDER_SRCS = ./
FUNC =		draw \
			errors \
			fc_parsing \
			init \
			keys_arrows \
			keys \
			map_validator \
			raycasting \
			s_parser \
			screenshot \
			settings_parser \
			settings \
			sprites \
			sprites2 \
			textures_parser \
			utils \
			gnl/get_next_line \
			gnl/get_next_line_utils \
			main
SRC = $(addprefix $(FOLDER_SRCS), $(FUNC))
OBJ = $(SRC:=.o)
LX_DIR = ./minilibx_mms/
LXFLAGS = -L. -lmlx -framework OpenGL -framework AppKit -g
LFT_DIR = ./libft/
LFTFLAGS = -L$(LFT_DIR) -lft

.PHONY: all clean fclean re norme lft lmlx

all: lmlx lft $(NAME)
	@echo "\033[32m[+] Make completed\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(INCLUDES) $(LXFLAGS) $(LFTFLAGS) -lm -o $(NAME)

lmlx:
	@$(MAKE) -C $(LX_DIR) --silent
	@cp ./minilibx_mms/libmlx.dylib .
	@echo  "\033[32m[+] Minilibx_mms builded\033[0m"

lft:
	@$(MAKE) -C $(LFT_DIR) --silent
	@$(MAKE) bonus -C $(LFT_DIR) --silent
	@echo  "\033[32m[+] Libft builded\033[0m"

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f screenshot.bmp
	@rm -f libmlx.dylib

re: fclean all