MAKEFLAGS	+= --silent

all:
	make -C mandatory

bonus:
	make -C bonus

clean:
	make -C bonus clean
	make -C mandatory clean

fclean:
	make -C bonus fclean
	make -C mandatory fclean

re: fclean all

.PHONY: all bonus clean fclean re
