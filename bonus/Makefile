#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 15:51:52 by edbernar          #+#    #+#              #
#    Updated: 2023/11/29 23:59:37 by eddy             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

MAKEFLAGS 		+= --silent

SRCS			=	main.c 																\
					parse_config_file/config_main.c										\
					graphics/main_graphics.c 											\
					graphics/load_textures/load_textures.c								\
					graphics/free_functions/free_all.c 									\
					graphics/free_functions/destroy_textures.c							\
					graphics/raycasting/mini_map/mini_map.c								\
					graphics/raycasting/inventory/inventory.c							\
					graphics/raycasting/main_raycasting.c								\
					graphics/main_menu/main_menu.c										\
					graphics/main_menu/solo_menu.c										\
					graphics/main_menu/multiplayer_menu.c								\
					graphics/main_menu/options_menu.c									\
					graphics/main_menu/button_action.c									\
					graphics/start_screen/start_screen.c								\
					graphics/larg_map/larg_map.c										\
					graphics/entry/keyboard/keyboard.c									\
					graphics/entry/keyboard/game_keyboard.c								\
					graphics/entry/keyboard/map_larg_menu_keyboard.c					\
					graphics/entry/mouse_whell.c										\
					graphics/entry/mouse_down.c											\
					graphics/entry/mouse_move.c											\
					graphics/entry/mouse_up.c											\
					graphics/debug/info_player.c										\
					graphics/init/init.c												\
					graphics/update.c													\
					networking/game_connexion/connect_server.c							\
					networking/game_connexion/print_network_err.c						\
					networking/game_connexion/manage_server_input.c						\
					networking/game_connexion/req_actions/player_disconnect.c			\
					networking/game_connexion/req_actions/receive_message.c				\
					networking/game_connexion/req_actions/set_player_attr.c				\
					networking/game_connexion/players_utils/create_online_player.c		\
					networking/game_connexion/players_utils/get_player_from_source.c	\
					networking/utils/current_timestamp.c								\
					networking/utils/ft_atof.c											\
					networking/utils/read_request.c										\
					networking/utils/socket_init.c										\
					parsing/check_map_lines.c 											\
					parsing/check_map_param.c 											\
					parsing/parse_file.c 												\
					parsing/parse_lines.c 												\
					parsing/set_map_blocks.c											\
					utils/first.c 														\
					free_map.c 															\

NAME			=	cub3d

OBJS			=	$(addprefix ./.build/, $(SRCS:.c=.o))

SV_SRCS			=	networking/server/server.c								\
					networking/server/manage_client.c						\
					networking/server/manage_client_input.c					\
					networking/utils/current_timestamp.c					\
					networking/utils/ft_atof.c								\
					networking/utils/read_request.c							\
					networking/utils/socket_init.c							\

SV_OBJS			=	$(addprefix ./.build/, $(SV_SRCS:.c=.o))

SV_NAME			=	cub3d_server

OBJ_DIR			=	$(sort $(dir $(OBJS) $(SV_OBJS)))

CC				=	gcc

CFLAGS			=	-Werror -Iincludes -Iincludes/libft -L./includes/libft -lft -Iincludes/MacroLibX/includes/ -lm -MD -g
# CFLAGS			=	-Wall -Werror -Wextra -Iincludes -Iincludes/libft -L./includes/libft -lft -Iincludes/MacroLibX/includes/ -lm -lSDL2

TOTAL_SRCS		= 	$(words $(SRCS))

COMPILED_SRCS 	= 	0

all : ${NAME} ${SV_NAME}

./.build/%.o : ./srcs/%.c
	@tput civis
	@$(CC) -c $(CFLAGS) "$<" -o "$@" 
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
        tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
    fi
	@echo "┌───────────────────────────────────────┐\n│\c"
	@if [ "$(COMPILED_SRCS)" -gt "0" ]; then \
        for i in $$(seq 0 $(shell echo "$$((($(COMPILED_SRCS) * 39) / $(TOTAL_SRCS)))")); do \
            printf "█"; \
        done; \
		for i in $$(seq 0 $(shell echo "$$(((($(TOTAL_SRCS) - $(COMPILED_SRCS)) * 39) / $(TOTAL_SRCS) - 1))")); do \
            printf " "; \
        done; \
    fi
	@echo "│\n└───────────────────────────────────────┘"
	@echo "[ $$(expr \( $(COMPILED_SRCS) \* 100 \) / $(TOTAL_SRCS))% ]\033[32m $< \033[0m"
	$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@tput cnorm

libft :
	@make -C "./includes/libft/"

mlx :
	@echo "── MLX ─────────────────────────"
	@make -C "./includes/MacroLibX/" -j
	@echo "────────────────────────────────"

$(OBJ_DIR):
	@mkdir -p $@

${NAME} : mlx libft $(OBJ_DIR) ${OBJS}
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
	fi
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
		echo "┌───────────────────────────────────────┐"; \
		echo "│███████████████████████████████████████│"; \
		echo "└───────────────────────────────────────┘"; \
		gcc ${OBJS} -o ${NAME} ./includes/MacroLibX/libmlx.so ${CFLAGS} -lSDL2; \
		echo "[ 100% ]\033[32m Compilation $(NAME) completed !\033[0m"; \
		echo "\n\033[32mThe program \"$(NAME)\" is ready !\033[0m"; \
	else \
		echo "\033[32mThe program \"$(NAME)\" is already ready !\033[0m"; \
	fi

${SV_NAME} : libft $(OBJ_DIR) ${SV_OBJS}
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
	fi
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
		echo "┌───────────────────────────────────────┐"; \
		echo "│███████████████████████████████████████│"; \
		echo "└───────────────────────────────────────┘"; \
		gcc ${SV_OBJS} -o ${SV_NAME} ${CFLAGS}; \
		echo "[ 100% ]\033[32m Compilation $(SV_NAME) completed !\033[0m"; \
		echo "\n\033[32mThe program \"$(SV_NAME)\" is ready !\033[0m"; \
	else \
		echo "\033[32mThe program \"$(SV_NAME)\" is already ready !\033[0m"; \
	fi

clean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "./includes/MacroLibX/" clean
	@echo "── CUB3D ───────────────────────"
	@make -C "./includes/libft/" clean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build

fclean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "./includes/MacroLibX/" fclean
	@echo "── CUB3D ───────────────────────"
	@rm -f ${NAME}
	@make -C "./includes/libft/" fclean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build

re	: fclean all

recub :
	@rm -f ${OBJS}
	@rm -f ${NAME}
	@echo "Files successfully cleaned (only cub3d's files)."
	@make all

-include $(OBJS:.o=.d)

.PHONY : libft mlx re fclean all clean create
