# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 22:27:47 by elopin            #+#    #+#              #
#    Updated: 2025/08/14 23:41:31 by lle-cout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -ggdb

SRCDIR = src/
SRCSF = main.c init.c ft_clean_up.c parsing.c draw.c cam_moove.c put_texture.c frame.c  small_map.c \
	door.c small_function.c calcul_for_draw.c draw_wall_tex.c draw_wall_tex2.c
SRCS = $(addprefix src/, $(SRCSF))

OBJDIR = objs/
OBJSF = $(SRCSF:.c=.o)
OBJS = $(addprefix objs/, $(OBJSF))

INCL = -I. -Iinc -Imlx -Ilibft
LIBFT_AR = libft/libft.a
MLX		= mlx/libmlx_Linux.a
MFLAGS	= -lmlx_Linux -lXext -lX11 -lm -lz -Lmlx -L/usr/lib

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(MLX)
	@make --no-print-directory -C libft
	@printf "\033[0m\033[1;35m|\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_AR) $(MLX) $(MFLAGS) -o $(NAME)
	@printf "\033[1;32mcub3d ready ✓\033[0m\n"

$(OBJDIR)%.o:$(SRCDIR)%.c
	@printf " \c"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

$(MLX):
	@make -C mlx

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[1;35mcub3d compiling... |\033[0m\033[45m\c\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\033[1;31mcub3d objects deleted\033[0m\n"
	@make -C mlx clean
	@printf "\033[1;31mmlx objects deleted\033[0m\n"
	@make --no-print-directory -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[1;31mcub3d binary file deleted\033[0m\n"
	@make -C mlx clean
	@printf "\033[1;31mmlx binary file deleted\033[0m\n"
	@make --no-print-directory -C libft fclean

re: fclean all

.PHONY: all clean fclean re
