# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/13 19:21:15 by Nikita_Kuyd       #+#    #+#              #
#    Updated: 2026/02/26 19:58:09 by nkuydin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = objects

SRCS = srcs/main.c \
		srcs/actions.c \
		srcs/exit_free.c \
		srcs/init.c \
		srcs/ft_atoi.c \
		srcs/monitor.c \
		srcs/routine.c \
		srcs/utils.c

OBJS = $(patsubst srcs/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) ${OBJS} -o $@
	@echo "${NAME} created successfully"

${OBJ_DIR}/%.o: srcs/%.c | ${OBJ_DIR}
	@mkdir -p ${dir $@}
	@${CC} $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}
	@echo "Created objects directory"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@rm -rf $(NAME) clean
	@echo "${NAME} removed"

re: fclean all

.PHONY: all clean fclean re leaks

#-g #-fsanitize=thread #-fsanitize=address
# valgrind --tool=helgrind --tool=drd ./philo 4 410 200 200 4