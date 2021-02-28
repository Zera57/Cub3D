# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/27 15:14:26 by hapryl            #+#    #+#              #
#    Updated: 2021/02/28 15:48:35 by hapryl           ###   ########.fr        #
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
LXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm
LFT_DIR = ./libft/
LFTFLAGS = -L$(LFT_DIR) -lft

.PHONY: all clean fclean re norme lft lmlx

all: lft $(NAME)
	@echo "\033[32m[+] Make completed\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(INCLUDES) $(LXFLAGS) $(LFTFLAGS) -lm -o $(NAME)

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