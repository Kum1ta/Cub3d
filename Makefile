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

SRCS			=	main.c 								\
					graphics/main_graphics.c 			\
					graphics/free_functions/free_all.c 	\
					graphics/map/larg_map.c 			\
					utils/first.c 						\

NAME			=	cub3d

OBJS			=	$(addprefix ./.build/, $(SRCS:.c=.o))

OBJ_DIR			=	$(sort $(dir $(OBJS)))

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -Iincludes -Iincludes/libft -L./includes/libft -lft -Iincludes/MacroLibX/includes/ -lm -lSDL2

TOTAL_SRCS		= 	$(words $(SRCS))

COMPILED_SRCS 	= 	0

all : ${NAME}

./.build/%.o : ./srcs/%.c
	@tput civis
	@$(CC) -c ./includes/MacroLibX/libmlx.so $(CFLAGS) "$<" -o "$@" 
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
		gcc ${OBJS} -o ${NAME} ./includes/MacroLibX/libmlx.so ${CFLAGS}; \
		echo "[ 100% ]\033[32m Compilation $(NAME) completed !\033[0m"; \
		echo "\n\033[32mThe program \"$(NAME)\" is ready !\033[0m"; \
	else \
		echo "\033[32mThe program \"$(NAME)\" is already ready !\033[0m"; \
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

.PHONY : libft mlx re fclean all clean create
