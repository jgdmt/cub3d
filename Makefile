SRCS			:=	main.c raycast.c raycast_bis.c cardinal_handler.c free.c parsing.c parsing_get.c parsing_utils.c events.c

OBJS			:= $(SRCS:.c=.o)

CC				:= cc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror  -I. #-ggdb3 -fsanitize=address
MLXFLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit  -L "/Users/$(USER)/.brew/opt/glfw/lib/" -I MLX42/include -lglfw
NAME			:= cub3D

all:			libmlx $(NAME) 

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

$(NAME):		$(OBJS) 
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS) libft/libft.a MLX42/build/libmlx42.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) MLX42/build

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean libmlx $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:

