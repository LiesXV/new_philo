# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:10:41 by ibenhaim          #+#    #+#              #
#    Updated: 2023/06/23 13:51:48 by ibenhaim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
FLAGS		=	-Wall -Werror -Wextra -pthread -O2 -fsanitize=thread -g3

HEADER		=	${INCLUDES}philo.h
SRCS		=	${SOURCES}main.c ${SOURCES}ft_atoi.c ${SOURCES}error_management.c ${SOURCES}thread_management.c \
				${SOURCES}mutex_management.c ${SOURCES}fork_management.c ${SOURCES}routine.c \
				${SOURCES}parse_and_assign.c ${SOURCES}utils.c

INCLUDES	=	includes/
SOURCES		=	sources/


OBJS		= 	${SRCS:.c=.o}


%.o:%.c ${HEADER}
				${CC} ${FLAGS} -c $< -o $@

${NAME}		: ${OBJS} ${HEADER}
				${CC} ${FLAGS} ${OBJS} -o ${NAME}

all : ${NAME}

clean:
				rm -f ${OBJS} 

fclean:	clean
				rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
