##
## This file is part of libbtarr.
##
## libbtarr is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## libbtarr is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with libbtarr.  If not, see <http://www.gnu.org/licenses/>.
##

CC		=	gcc -fPIC -shared

NAME		=	libbtarr.so

SRCS		=	btarr.c

OBJS		=	$(SRCS:.c=.o)

NAME_TEST	=	test
SRCS_TEST	=	main.c
OBJS_TEST	=	$(SRCS_TEST:.c=.o)
LDFLAGS_TEST	=	-L. -lbtarr -Wl,-rpath=.

CFLAGS		+=	-W -Wall -Wextra

RM		=	rm -rf

all		:	$(NAME) $(NAME_TEST)

$(NAME)		:	$(OBJS)
			gcc -shared -fPIC -o $(NAME) $(OBJS)

clean		:
			$(RM) $(NAME)
			$(RM) $(NAME_TEST)

fclean		:	clean
			$(RM) $(OBJS)
			$(RM) $(OBJS_TEST)

re		:	fclean all

test		:	$(NAME) $(OBJS_TEST)
			gcc -o $(NAME_TEST) $(OBJS_TEST) $(LDFLAGS_TEST)

.PHONY		:	all clean fclean re test
