NAME		=	eval_formula

SRCS		=	main.cpp\
				eval_formula.cpp\
				../inc/utils.cpp\

OBJS		=	${SRCS:.cpp=.o}

INCLUDES	= 	-I ../inc/

CC			=	clang++ -gdwarf-4 -Wall -Wextra -Werror 



all			:	${NAME}

${NAME}		:	${OBJS} 
					${CC} $(INCLUDES) -o $@ $^ 

%.o			:	%.cpp
					$(CC) ${INCLUDES} -o $@ -c $^ 

clean		:
					rm -rf ${OBJS} tree.png

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re 
