NAME	=	philo

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INCLUDE = -I philo.h

SRCS	=	0_utils.c				\
			1_error.c				\
			2_parsing.c				\
			3_malloc_free_philo.c	\
			4_time_handling.c		\
			5_fork_mutex_init.c		\
			6_threads_init.c	\
			7_fork_locking.c		\
			8_routine.c				\
			9_death.c				\
			10_writing.c			\
			main.c					\

OBJS	=			$(SRCS:.c=.o)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

all :		$(NAME)

clean:		
			@rm -f $(OBJS)
			
fclean:		clean
			@rm -f $(NAME)

re:			fclean all