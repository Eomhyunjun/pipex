# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/06/10 20:11:53 by heom             ###   ########.fr        #
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



MAND_OBJS = $(MAND_FIL:.c=.o)
BONUS_OBJS = $(BONUS_FIL:.c=.o)

MAND_FIL = $(addsuffix .c, $(addprefix mand/, $(MAND_SRCS))) \

BONUS_FIL = $(addsuffix .c, $(addprefix bonus/, $(MAND_SRCS))) \


all : $(NAME)

$(MAND_OBJS): %.o : %.c
	gcc $(CFLAGS) -c -o $@ $<


$(NAME) : $(MAND_OBJS)
	gcc $(CFLAGS) $^ -o $@

$(NAME)_bonus: $(BONUS_OBJS)
	gcc $(CFLAGS) $^ -o $@


clean :
	$(RM) $(MAND_OBJS) $(BONUS_OBJS)

fclean : clean
	$(RM) $(NAME)

test :
	gcc $(CFLAGS) src/*.c operate/*.c libft/*.c test.c -o test

bonus:


re: fclean all

.PHONY: all, clean, fclean, re, bonus, test
