# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 17:20:50 by edbernar          #+#    #+#              #
#    Updated: 2024/03/12 13:06:34 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	Char_Compare/ft_isalnum.c \
					Char_Compare/ft_isalpha.c \
					Char_Compare/ft_isascii.c \
					Char_Compare/ft_isdigit.c \
					Char_Compare/ft_isnumber.c \
					Char_Compare/ft_isprint.c \
					Char_Compare/ft_isspace.c \
					Char_Compare/ft_tolower.c \
					Char_Compare/ft_toupper.c \
					Convertion/ft_atoi.c \
					Convertion/ft_itoa.c \
					Convertion/ft_atol.c \
					Convertion/ft_ultoa_base.c \
					Lists/ft_lstadd_back.c \
					Lists/ft_lstadd_front.c \
					Lists/ft_lstclear.c \
					Lists/ft_lstdelone.c \
					Lists/ft_lstiter.c \
					Lists/ft_lstlast.c \
					Lists/ft_lstmap.c \
					Lists/ft_lstnew.c \
					Lists/ft_lstsize.c \
					File/get_file.c \
					File/gnl/get_next_line.c \
					File/gnl/get_next_line_utils.c \
					Memory/ft_bzero.c \
					Memory/ft_calloc.c \
					Memory/ft_memchr.c \
					Memory/ft_memcmp.c \
					Memory/ft_memcpy.c \
					Memory/ft_memmove.c \
					Memory/ft_memset.c \
					Output/ft_putchar_fd.c \
					Output/ft_putchar_rep.c \
					Output/ft_putendl_fd.c \
					Output/ft_putnbr_fd.c \
					Output/ft_putptr_fd.c \
					Output/ft_putstr_fd.c \
					Output/ft_putunbr_fd.c \
					Output/ft_putxnbr_fd.c \
					Output/printf/ft_printf.c \
					Output/printf/utils/combinaison_flag.c \
					Output/printf/utils/conversion_flag.c \
					Output/printf/utils/print_functions/ft_printf_char.c \
					Output/printf/utils/print_functions/ft_printf_hexa.c \
					Output/printf/utils/print_functions/ft_printf_int.c \
					Output/printf/utils/print_functions/ft_printf_ptr.c \
					Output/printf/utils/print_functions/ft_printf_string.c \
					Output/printf/utils/print_functions/ft_printf_uint.c \
					Strings/ft_split.c \
					Strings/ft_strchr.c \
					Strings/ft_strcmp.c \
					Strings/ft_strdup.c \
					Strings/ft_striteri.c \
					Strings/ft_strjoin.c \
					Strings/ft_strlcat.c \
					Strings/ft_strlcpy.c \
					Strings/ft_strlen.c \
					Strings/ft_strmapi.c \
					Strings/ft_strncmp.c \
					Strings/ft_strncpy.c \
					Strings/ft_strnstr.c \
					Strings/ft_strrchr.c \
					Strings/ft_strtrim.c \
					Strings/ft_substr.c \

HEAD			=  ./libft.h

NAME			=	libft.a

OBJS			=	${SRCS:.c=.o}

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra

TOTAL_SRCS		= 	$(words $(SRCS))

COMPILED_SRCS 	= 	0

all : ${NAME}

%.o : %.c
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
	@sleep 0.05
	$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@tput cnorm

${NAME} : ${OBJS}
	@ar rc ${NAME} ${OBJS} ${HEAD}
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
	@echo "┌───────────────────────────────────────┐"
	@echo "│███████████████████████████████████████│"
	@echo "└───────────────────────────────────────┘"
	@echo "[ 100% ]\033[32m Compilation libft completed !\033[0m"

clean :
	@rm -f ${OBJS}

fclean : clean
	@rm -f ${NAME}

re	: fclean all

.PHONY : re fclean all clean bonus
