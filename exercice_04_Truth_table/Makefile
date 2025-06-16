NAME		=	print_truth_table
LIB			=	${NAME}.a

_SRCS		=	main.cpp print_truth_table.cpp
SDIR		=	srcs
SRCS		=	$(patsubst %,$(SDIR)/%,$(_SRCS))

ODIR		=	objs
OBJS		=	$(subst ${SDIR},$(ODIR),${SRCS:.cpp=.o})

INCLUDES	=	-I includes -I ../exercice_03_Boolean_evaluation/includes
LIBEXT		=	../exercice_03_Boolean_evaluation/eval_formula.a
DEP			=	$(OBJS:%.o=%.d)

CC			=	clang++  
CFLAGS		=	-Wall -Wextra -Werror


all			:	${LIBEXT} ${ODIR} ${NAME}

${NAME}		:   ${OBJS} 
					${CC} ${CFLAGS} $(INCLUDES) $^ -o $@ ${LIBEXT} 
${LIBEXT}	:
				make -C $(dir ${LIBEXT}) lib

${ODIR}		:
				mkdir -p objs

-include $(DEP)
$(ODIR)/%.o :	${SDIR}/%.cpp
					${CC} ${CFLAGS} ${INCLUDES} -MMD -c $< -o $@ 

lib			:	${ODIR} ${LIB}			

${LIB}		:	${OBJS}
					ar rc $@ $(subst ${ODIR}/main.o,,$^) 

clean		:
					rm -rf ${ODIR} *.png *.log

fclean		:	clean
					rm -rf $(NAME) ${LIB}

re			:	fclean all

.PHONY		:	all clean fclean re 
