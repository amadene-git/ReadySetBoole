NAME		=	negation_normal_form

SRCS		=	main.cpp\
				negation_normal_form.cpp\
				../ex03/eval_formula.cpp\
				../ex04/print_truth_table.cpp\
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
					rm -rf ${OBJS} 

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re 
