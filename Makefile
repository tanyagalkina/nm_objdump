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

NMSRCS	=	./nm/main.c 		\

OBJSRCS	=	./obj/main.c 		\
		./obj/my_dump_first.c	\
		./obj/error64.c		\
		./obj/show_file.c	\
		./obj/sections.c	\
		./obj/print_tools.c	\
		./obj/show_sections.c


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
	$(RM) $(OBJOBJS)
	$(RM) $(NMOBJS)

fclean: clean
	$(RM) ./my_nm
	$(RM) ./my_objdump
:
re: fclean all

.PHONY: all nm objdump clean fclean re
