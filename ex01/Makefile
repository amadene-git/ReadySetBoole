NAME		=	multiplier

SRCS		=	main.cpp\
				multiplier.cpp\
				../ex00/adder.cpp\

OBJS		=	${SRCS:.cpp=.o}

INCLUDES	= 	-I . -I ../ex00

CC			=	g++ -Wall -Wextra -Werror

all			:	${NAME}

${NAME}		:	${OBJS}
					${CC} -o $@ $^

%.o			:	%.cpp
					$(CC) -o $@ -c $^

clean		:
					rm -rf ${OBJS}

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
