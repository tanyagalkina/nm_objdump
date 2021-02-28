##
## EPITECH PROJECT, 2020
## nm_objdump
## File description:
## Makefile
##


NMNAME	= my_nm

OBJNAME	= my_objdump

CC	= gcc

RM	= rm -f

NMSRCS	=	./nm/main.c \

OBJSRCS	=	./obj/main.c \

NMOBJS	= $(NMSRCS:.c=.o)
OBJOBJS	= $(OBJSRCS:.c=.o)

CFLAGS = -I ./nm/include/ -I ./core/include/ -I ./objdump/include/
CFLAGS += -W -Wall -Wextra

all: nm objdump

nm: $(NMOBJS)
	$(CC) $(NMOBJS) -o $(NMNAME) $(LDFLAGS)

objdump: $(OBJOBJS)
	$(CC) $(OBJOBJS) -o $(OBJNAME) $(LDFLAGS)

clean:
	$(RM) ./my_nm
	$(RM) ./my_objdump

fclean: clean
	make fclean -C nm/
	make fclean -C objdump/

re: fclean all

.PHONY: all nm objdump clean fclean re