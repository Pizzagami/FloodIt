NAME = Flood-It_Partie1

SRCS = ./API_Gene_instance.c \
		./API_Grille_txt.c	 \
		./biblio_zone.c		 \
		./Flood-It_Partie1.c \
		./Fonctions_exo1.c	 \
		./graphe_zone.c		 \
		./Liste_case.c

OBJS = ${SRCS:.c=.o}

CC = gcc


${NAME}	:	${OBJS}
	${CC}	 -o ${NAME}  ${OBJS}

all:  ${NAME}

clean:	
	${RM}	${OBJS}

fclean:  clean
	${RM} ${NAME}

re: fclean all
	${RM}	${OBJS}