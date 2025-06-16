NAME		=	test_eval_formula
LIB			=	../eval_formula.a

_SRCS		=	test.cpp

_OBJS		=	${_SRCS:.cpp=.o}

INCLUDES	=	-I ../includes

CC			=	clang++  
CFLAGS		=	-Wall -Wextra -Werror


all			:	${NAME}

${NAME}		:   ${LIB} 
					${CC} ${CFLAGS} $(INCLUDES) -c ${_SRCS} -o ${_OBJS} 
					${CC} ${CFLAGS} $(INCLUDES) ${_OBJS} -o $@ ${LIB} 

${LIB}		:
				make -C ../ lib

clean		:
					rm -rf ${_OBJS} *.png *.log

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re 
