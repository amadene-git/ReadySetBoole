NAME		=	adder

SRCS		=	main.cpp\
				adder.cpp\


OBJS		=	${SRCS:.cpp=.o}

CC			=	g++ -Wall -Wextra -Werror

all			:	${NAME}

${NAME}		:	${OBJS}
					${CC} $(INCLUDES) -o $@ $^

%.o			:	%.cpp
					$(CC) ${INCLUDES} -o $@ -c $^

clean		:
					rm -rf ${OBJS}

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
