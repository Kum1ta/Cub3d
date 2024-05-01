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

SRCS			=	main_bonus.c 																\
					parse_config_file/config_main_bonus.c										\
					parse_config_file/utils_bonus.c												\
					parse_config_file/config_parser_bonus.c										\
					graphics/main_graphics_bonus.c 												\
					graphics/draw_image_to_window_bonus.c 										\
					graphics/load_textures/load_textures_bonus.c								\
					graphics/free_functions/free_all_bonus.c									\
					graphics/free_functions/destroy_textures_bonus.c							\
					graphics/raycasting/mini_map/mini_map_bonus.c								\
					graphics/raycasting/inventory/inventory_bonus.c								\
					graphics/raycasting/inventory/item_effect_bonus.c							\
					graphics/raycasting/inventory/put_actual_item_bonus.c						\
					graphics/raycasting/main_raycasting_bonus.c									\
					graphics/raycasting/raycast_bonus.c											\
					graphics/raycasting/show_popup_bonus.c										\
					graphics/raycasting/draw/supersampling_bonus.c								\
					graphics/raycasting/draw/sprites/draw_sprites_bonus.c						\
					graphics/raycasting/draw/sprites/draw_sprite_bonus.c						\
					graphics/raycasting/draw/sprites/get_sprites_list_bonus.c					\
					graphics/raycasting/draw/sprites/set_sprites_attr_bonus.c					\
					graphics/raycasting/draw/draw_wall_line_bonus.c								\
					graphics/raycasting/draw/draw_ceil_floor_bonus.c							\
					graphics/main_menu/main_menu_bonus.c										\
					graphics/main_menu/multiplayer_menu_bonus.c									\
					graphics/main_menu/options_menu_bonus.c										\
					graphics/main_menu/button_action_one_bonus.c								\
					graphics/main_menu/button_action_two_bonus.c								\
					graphics/main_menu/options_list_button_one_bonus.c							\
					graphics/main_menu/options_list_button_two_bonus.c							\
					graphics/main_menu/options_seleted_bonus.c									\
					graphics/main_menu/options_part_bonus.c										\
					graphics/start_screen/start_screen_bonus.c									\
					graphics/larg_map/larg_map_bonus.c											\
					graphics/larg_map/button_action_bonus.c										\
					graphics/larg_map/draw_map_bonus.c											\
					graphics/larg_map/init_bonus.c												\
					graphics/larg_map/list_button_bonus.c										\
					graphics/larg_map/sensibility_bonus.c										\
					graphics/larg_map/settings_bonus.c											\
					graphics/entry/keyboard/keyboard_bonus.c									\
					graphics/entry/keyboard/game_keyboard_bonus.c								\
					graphics/entry/keyboard/map_larg_menu_keyboard_bonus.c						\
					graphics/entry/keyboard/key_down_type_bonus.c								\
					graphics/entry/mouse_whell_bonus.c											\
					graphics/entry/mouse_down_bonus.c											\
					graphics/entry/mouse_move_bonus.c											\
					graphics/entry/mouse_up_bonus.c												\
					graphics/dead_screen/dead_screen_bonus.c									\
					graphics/init/init_bonus.c													\
					graphics/update_bonus.c														\
					networking/game_connexion/connect_server_bonus.c							\
					networking/game_connexion/print_network_err_bonus.c							\
					networking/game_connexion/manage_server_input_bonus.c						\
					networking/game_connexion/req_actions/player_disconnect_bonus.c				\
					networking/game_connexion/req_actions/receive_message_bonus.c				\
					networking/game_connexion/req_actions/set_door_state_bonus.c				\
					networking/game_connexion/req_actions/set_player_attr_bonus.c				\
					networking/game_connexion/req_actions/shoot_bonus.c							\
					networking/game_connexion/req_actions/health_kit_bonus.c					\
					networking/game_connexion/players_utils/create_online_player_bonus.c		\
					networking/game_connexion/players_utils/get_player_from_source_bonus.c		\
					networking/game_connexion/add_popup_bonus.c									\
					networking/utils/current_timestamp_bonus.c									\
					networking/utils/read_request_bonus.c										\
					networking/utils/socket_init_bonus.c										\
					parsing/can_exit_map_bonus.c												\
					parsing/check_map_lines_bonus.c												\
					parsing/check_map_param_bonus.c												\
					parsing/parse_file_bonus.c													\
					parsing/parse_lines_bonus.c													\
					parsing/set_map_blocks_bonus.c												\
					utils/first_bonus.c															\
					utils/vector_bonus.c														\
					free_map_bonus.c															\

NAME			=	cub3D

OBJS			=	$(addprefix ./.build/, $(SRCS:.c=.o))

OBJ_DIR			=	$(sort $(dir $(OBJS)))

MACROLIBX		=	../Libs/MacroLibX/libmlx.so

LIBFT			=	../Libs/libft/libft.a

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra -Iincludes -I$(dir $(LIBFT)) -I$(dir $(MACROLIBX))/includes/ -MD

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

$(LIBFT) :
	@make -C "$(dir $(LIBFT))"

$(MACROLIBX) :
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" -j
	@echo "────────────────────────────────"

$(OBJ_DIR):
	@mkdir -p $@

${NAME} : $(MACROLIBX) $(LIBFT) $(OBJ_DIR) ${OBJS}
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
		${CC} ${OBJS} -o ${NAME} $(MACROLIBX) ${CFLAGS} -L$(dir $(LIBFT)) -lft -lm -lSDL2; \
		echo "[ 100% ]\033[32m Compilation $(NAME) completed !\033[0m"; \
		echo "\n\033[32mThe program \"$(NAME)\" is ready !\033[0m"; \
	else \
		echo "\033[32mThe program \"$(NAME)\" is already ready !\033[0m"; \
	fi

${SV_NAME} : $(LIBFT) $(OBJ_DIR) ${SV_OBJS}
	make -f Makefile_SV


clean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" clean
	@echo "── CUB3D ───────────────────────"
	@make -C "$(dir $(LIBFT))" clean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build
	@make -f Makefile_SV clean

fclean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" fclean
	@echo "── CUB3D ───────────────────────"
	@rm -f ${NAME}
	@make -C "$(dir $(LIBFT))" fclean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build
	@make -f Makefile_SV fclean

re	: fclean all

recub :
	@rm -f ${OBJS}
	@rm -f ${NAME}
	@echo "Files successfully cleaned (only cub3d's files)."
	@make all

-include $(OBJS:.o=.d)

.PHONY : libft mlx re fclean all clean create $(NAME)
