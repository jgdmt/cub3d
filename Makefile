SRCS			:=	main.c raycast.c raycast_bis.c cardinal_handler.c free.c parsing.c parsing_get.c parsing_utils.c events.c parsing_split.c

SRCB_EVENTS		:=	events_bonus.c events_gun_bonus.c events_level_bonus.c events_portals_bonus.c events_mouse_bonus.c
SRCB_PARSING	:=	parsing_bonus.c parsing_get_bonus.c parsing_utils_bonus.c parsing_split_bonus.c parsing_getbon_bonus.c
SRCB_RAYCAST	:=	raycast_bonus.c raycast_bis_bonus.c raycast_floor_sky_casting.c raycast_portal_bonus.c
SRCB			:=  main_bonus.c cardinal_handler_bonus.c free_bonus.c loading_bonus.c 
SRCS_BONUS		:=	$(SRCB) $(addprefix events/,$(SRCB_EVENTS)) $(addprefix parsing/,$(SRCB_PARSING)) $(addprefix raycast/,$(SRCB_RAYCAST)) 

OBJS			:= $(SRCS:.c=.o)

OBJS_BONUS 		:= $(addprefix bonus/,$(SRCS_BONUS:.c=.o))

CC				:= cc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror  -I. -O3 -Ofast -fsanitize=address -ggdb3
MLXFLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit  -L "/Users/$(USER)/.brew/opt/glfw/lib/" -I MLX42/include -lglfw
NAME			:= cub3D
NAME_BONUS		:= potato4D

all:			libmlx $(NAME) 

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

$(NAME):		$(OBJS) 
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS) libft/libft.a MLX42/build/libmlx42.a

bonus:			libmlx $(NAME_BONUS)

$(NAME_BONUS):		$(OBJS_BONUS) 
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) libft/libft.a MLX42/build/libmlx42.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)
				$(RM) MLX42/build

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean libmlx $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:

