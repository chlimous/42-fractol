# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chlimous <chlimous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 00:00:00 by chlimous          #+#    #+#              #
#    Updated: 2024/11/29 22:24:22 by chlimous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRCDIR = src
OBJDIR = obj
SRCS = $(addprefix $(SRCDIR)/, animations.c colors.c complex.c fractol.c hooks.c main.c mapping.c mlx.c parser.c parser_utils.c sets.c utils.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
INCLUDE = include
INCLUDES = -I $(INCLUDE) -I $(LIBFT_DIR)/include -I $(MINILIBX_DIR) -I /usr/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
C_GREEN=\e[32m
C_END=\e[0m

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDE) $(MINILIBX)
	@mkdir -p $(dir $@)
	$(CC) -O3 $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -l ft -L $(MINILIBX_DIR) -l mlx_Linux -L /usr/lib -lXext -lX11 -lm -lz -o $(NAME)

bonus: all

$(MINILIBX):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux "$(MINILIBX_DIR)"; \
	fi
	@make -C $(MINILIBX_DIR)

$(LIBFT): FORCE
	@echo "$(C_GREEN)Compiling libft...$(C_END)"
	@output="$$(make -C libft)"; \
	if echo "$$output" | grep -q 'is up to date'; then \
		echo "$(C_GREEN)libft is already up to date.$(C_END)"; \
	else \
		echo "$(C_GREEN)libft succesfully compiled.$(C_END)"; \
	fi

FORCE:

clean:
	rm -rf $(OBJDIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR); \
	fi
	@if [ -d "$(MINILIBX_DIR)" ]; then \
		make clean -C $(MINILIBX_DIR); \
	fi

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi
	rm -rf $(MINILIBX_DIR)

re: fclean all

.PHONY: all FORCE clean fclean re
