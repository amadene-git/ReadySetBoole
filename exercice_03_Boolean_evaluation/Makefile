NAME		=	eval_formula


_SRCS		=	main.cpp eval_formula.cpp
SDIR		=	srcs
SRCS		=	$(patsubst %,$(SDIR)/%,$(_SRCS))

_OBJS		=	${SRCS:.cpp=.o}
ODIR		=	objs
OBJS		=	$(subst ${SDIR},$(ODIR),$(_OBJS))

INCLUDES	=	-I includes
DEP			=	$(OBJS:%.o=%.d)

CC			=	clang++  
CFLAGS		=	-Wall -Wextra -Werror


all			:	${ODIR} ${NAME}

${NAME}		:   ${OBJS} 
					${CC} ${CFLAGS} $(INCLUDES) $^ -o $@ 

${ODIR}		:
				mkdir -p objs

-include $(DEP)
$(ODIR)/%.o :	${SDIR}/%.cpp
					${CC} ${CFLAGS} ${INCLUDES} -MMD -c $< -o $@ 

clean		:
					rm -rf ${ODIR} *.png *.log

fclean		:	clean
					rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re 
