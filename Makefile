# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/06/16 13:23:52 by heom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

MAND_SRCS = main \
			safe_exit \
			all \
			malloc_fd \
			make_pipe \
			fork_loop \
			utils/px_split \
			utils/px_strlcpy \
			utils/px_strjoin \

BONUS_SRCS = main \
			safe_exit \
			all \
			malloc_fd \
			make_pipe \
			fork_loop \
			utils/px_split \
			utils/px_strlcpy \
			utils/px_strjoin \

MAND_OBJS = $(MAND_FIL:.c=.o)
BONUS_OBJS = $(BONUS_FIL:.c=.o)

MAND_FIL = $(addsuffix .c, $(addprefix mand/, $(MAND_SRCS))) \

BONUS_FIL = $(addsuffix _bonus.c, $(addprefix bonus/, $(MAND_SRCS))) \


all : $(NAME)

$(MAND_OBJS): %.o : %.c
	gcc $(CFLAGS) -c -o $@ $<


$(NAME) : $(MAND_OBJS)
	gcc $(CFLAGS) $^ -o $@

clean :
	$(RM) $(MAND_OBJS) $(BONUS_OBJS)

fclean : clean
	$(RM) $(NAME)

bonus: $(BONUS_OBJS)
	gcc $(CFLAGS) $^ -o $(NAME)





re: fclean all

.PHONY: all clean fclean re bonus
