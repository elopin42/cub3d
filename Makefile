# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 22:27:47 by elopin            #+#    #+#              #
#    Updated: 2025/09/05 18:46:08 by lle-cout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -ggdb # -O3 -flto -ffast-math -march=native -pipe
LINK = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

MAKE = make --no-print-directory
MAKE_LIBFT = $(MAKE) -C libft/
MAKE_MLX = $(MAKE) -C mlx
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

SRCS = src/parser/check_config.c src/parser/error_handlers.c src/parser/flood_fill.c src/parser/format_map.c src/parser/get_config.c src/parser/get_map.c src/parser/load_file.c src/parser/parser.c src/parser/utils.c src/parser/rgb_check.c \
	src/init_game/error_handlers.c src/init_game/init.c src/init_game/textures.c \
	src/raycasting/calcul_for_draw.c src/raycasting/cam_moove.c src/raycasting/destroy.c src/raycasting/door.c src/raycasting/draw.c src/raycasting/draw_wall_tex2.c src/raycasting/draw_wall_tex.c src/raycasting/flashlight.c \
	src/main.c src/raycasting/put_texture.c src/raycasting/small_function.c src/raycasting/minimap.c src/raycasting/pixel_draw_utils.c src/raycasting/overlay.c src/raycasting/wrappers_draw.c

OBJ_DIR = obj
OBJ = $(SRCS:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[32m
YELLOW = \e[0;33m
RED = \e[0;31m
RESET = \033[0m

all: $(NAME)

bonus: all

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LINK) -o $(NAME)
	@printf "$(GREEN)cub3d ready!$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling %-30s$(RESET)\r" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE_LIBFT) all

$(MLX):
	@$(MAKE_MLX) > /dev/null
	@printf "$(GREEN)mlx done ✅$(RESET)\n"

clean:
	@$(MAKE_LIBFT) clean
	@printf "$(RED)libft objects deleted$(RESET)\n"
	@$(MAKE_MLX) clean > /dev/null
	@printf "$(RED)mlx deleted$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)cub3d objects deleted$(RESET)\n"

fclean: clean
	@$(MAKE_LIBFT) fclean
	@printf "$(RED)libft.a deleted$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(RED)cub3d deleted$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus
