# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elopin <elopin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 22:27:47 by elopin            #+#    #+#              #
#    Updated: 2025/07/01 21:00:47 by elopin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3d
FLAGS=-Wall -Wextra -Werror -g3
SRCSF=main.c \
	  init.c \
	  ft_clean_up.c \
	  parsing.c	\
	  get_next_line.c \
	  get_next_line_utils.c \
	  tools.c \
	  ft_split.c \
	  draw.c \
	  cam_moove.c \
	  put_texture.c \
	  frame.c  \
	  small_map.c
OBJSF=$(SRCSF:.c=.o)
SRCDIR=srcs/
OBJDIR=objs/
SRCS=$(addprefix srcs/, $(SRCSF))
OBJS=$(addprefix objs/, $(OBJSF))
MFLAGS	= -lmlx_Linux -lXext -lX11 -lm -lz -Lmlx -L/usr/lib
MLX		= mlx/libmlx_Linux.a
INCL = -I. -Iinc -Imlx

all: $(NAME)

$(NAME): $(OBJDIR) $(MLX) $(OBJS)
	@echo "\033[0m\033[1;35m|\033[0m"
	@cc $(FLAGS) -o $(NAME) $(OBJS) $(MFLAGS)
	@echo "\033[1;32mcub3d ready ✓\033[0m"

$(OBJDIR)%.o:$(SRCDIR)%.c
	@echo " \c"
	@cc $(FLAGS) -I. -c $^ -o $@ $(INCL)

$(MLX):
	@make -C mlx

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "\033[1;35mcub3d compiling... |\033[0m\033[45m\c"

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[1;31mcub3d objects deleted\033[0m"
	@make -C mlx clean
	@echo "\033[1;31mmlx objects deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;31mcub3d binary file deleted\033[0m"
	@make -C mlx clean
	@echo "\033[1;31mmlx binary file deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
