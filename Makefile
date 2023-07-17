NAME		=	so_long

SRC			=	main.c \
				parsing.c \
				mlx_fcnt.c

OBJ			=	$(SRC:.c=.o)

CC			=	clang

CFLAGS		=	-g -Wall -Wextra -Werror

MLXFLAGS	=	-lXext -lX11

LIB.A		=	libft/libft.a

MLX.A		=	mlx/libmlx.a

all:			$(NAME)

$(NAME):		$(OBJ)
					make -sC libft
					make -sC mlx
					clang $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIB.A) $(MLX.A) -o $(NAME)

clean:
					make clean -sC libft
					make clean -sC mlx
					rm -f $(OBJ)

fclean:			clean
					make fclean -sC libft
					rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
