NAME = libft.a
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror

GREEN = \033[32m
YELLOW = \e[0;33m
RESET = \033[0m

SRCDIR = src
OBJDIR = obj

SRCS = \
src/ft_arraylen.c src/ft_atoi.c src/ft_atoll.c src/ft_bzero.c src/ft_calloc.c \
src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c src/ft_isspace.c \
src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c src/ft_print_strarray.c \
src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putbase_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c \
src/ft_strchr.c src/ft_strcmp.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c src/ft_strlcat.c \
src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c \
src/ft_strstr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c src/ft_printf.c \
src/get_next_line.c

OBJ = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@printf "$(GREEN)libft.a done ✅                      $(RESET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "$(YELLOW)Compiling %-30s$(RESET)\r" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
