# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 00:00:00 by student           #+#    #+#              #
#    Updated: 2025/07/30 21:55:22 by muzz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SOURCES = main.c \
          parsing/parse_map.c \
          parsing/parse_textures.c \
          parsing/validation.c \
          raycasting/raycasting.c \
          raycasting/dda.c \
          raycasting/texture.c \
          raycasting/texture2.c \
          raycasting/texture3.c \
          rendering/rendering.c \
          rendering/draw.c \
          game/game_loop.c \
          game/movement.c \
          game/input.c \
          utils/utils.c \
          utils/string_utils.c \
          utils/cleanup.c \
          utils/cleanup_textures.c \
          utils/error.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INCDIR) -I/usr/include -Imlx_linux -O3
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "$(BLUE)Building MLX library...$(RESET)"
	@make -C $(MLX_DIR)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
