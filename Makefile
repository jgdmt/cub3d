SRCS			:=	main.c raycast.c bis.c cardinal_handler.c free.c parsing.c parsing_get.c parsing_utils.c events.c parsing_split.c

SRCB_HUD		:=  main_bonus.c health_bar_bonus.c minimap_bonus.c
SRCB_INIT		:=	gunstext_bonus.c data_bonus.c map_bonus.c player_bonus.c assets_bonus.c datatext_bonus.c thread.c
SRCB_EVENTS		:=	bonus.c math_bonus.c move_bonus.c tp_bonus.c menu_bonus.c gun_bonus.c level_bonus.c portals_bonus.c mouse_bonus.c resize_bonus.c
SRCB_PARSING	:=	bonus.c get_bonus.c utils_bonus.c split_bonus.c getbon_bonus.c
SRCB_RAYCAST	:=	bonus.c cast_bonus.c floor_sky_casting_bonus.c portal_bonus.c tools_bonus.c main_bonus.c sprite_bonus.c
SRCB			:=  main_bonus.c free_bonus.c loading_bonus.c  inertia_bonus.c thread_tools_bonus.c
SRCS_BONUS		:=	$(SRCB) $(addprefix init/init_,$(SRCB_INIT)) $(addprefix events/events_,$(SRCB_EVENTS)) $(addprefix HUD/hud_,$(SRCB_HUD)) $(addprefix parsing/parsing_,$(SRCB_PARSING)) $(addprefix raycast/raycast_,$(SRCB_RAYCAST)) 

OBJS			:= $(SRCS:.c=.o)

OBJS_BONUS 		:= $(addprefix bonus/,$(SRCS_BONUS:.c=.o))

CC				:= cc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror  -I. -O3 -Ofast -ffast-math #-fsanitize=thread -ggdb3
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

