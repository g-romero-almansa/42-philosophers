# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 13:19:52 by gromero-          #+#    #+#              #
#    Updated: 2023/01/17 13:21:24 by gromero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	source/philo.c
OBJ_SRC		=	 $(SRC:.c = .o)

EXEC		=	philo

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

all:		$(EXEC)

$(NAME):	all

$(EXEC):	$(OBJ_SRC)
	$(CC)	$(CFLAGS)	$(OBJ_SRC)	-o	$(EXEC)

clean:
	rm -f $(EXEC)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
