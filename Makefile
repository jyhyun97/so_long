# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeonhyun <jeonhyun@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/03 13:53:30 by jeonhyun          #+#    #+#              #
#    Updated: 2021/07/09 15:36:16 by jeonhyun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
FLAGS = -Wall -Wextra -Werror
SRCS = src/main.c\
	   src/split.c\
	   src/ft_itoa.c\
	   src/util.c\
	   src/init.c\
	   src/move.c\
	   src/screen.c
OBJS = $(SRCS:.c=.o)

.c.o :
	gcc $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@gcc $(FLAGS) -L./mlx -lmlx -framework OpenGL -framework Appkit $(OBJS) -o $(NAME)	

all : $(NAME)

clean :
	rm -rf $(OBJS)
fclean :	clean
	rm -rf $(NAME)
re :	fclean all

.PHONY : all clean fclean re
