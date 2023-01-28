# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 13:17:51 by fraqioui          #+#    #+#              #
#    Updated: 2023/01/11 13:17:53 by fraqioui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = pipex

CC = cc 
FLAGS = -Wall -Wextra -Werror
HEADER = pipex.h ft_printf/ft_printf.h
RM = rm -rf

FILES =	exec \
		helpers \
		main \
		utils_1 \
		utils_2 \
		evol \
		exec_help \
		ft_printf/hex \
		ft_printf/number \
		ft_printf/start \
		ft_printf/string 

FOBJ = ${FILES:=.o}

.PHONY = all clean fclean re

all: ${NAME}

${NAME}: ${FOBJ} ${HEADER}
	${CC} ${FLAGS} ${FOBJ} -o ${NAME}

%.o: %.c 
	${CC} ${FLAGS} -c $< -o $@

clean:
	${RM} ${FOBJ}
fclean: clean
	${RM} ${NAME}
re: all fclean
