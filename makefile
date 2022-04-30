pathSeparator = /

INCLUDEDIR = .$(pathSeparator)include
# INCLUDEDIR += .$(pathSeparator)include$(pathSeparator)SDL_include
DEL_COMMAND  = rm
CC = gcc
CFLAG = -g -I$(INCLUDEDIR) -no-pie

SRCDIR = .$(pathSeparator)src
BUILDDIR = .$(pathSeparator)build
# LIBDIR = .$(pathSeparator)lib
OBJDIR = .$(pathSeparator)obj

NAME = game_of_life

all : init_folder $(NAME)

$(NAME) : $(OBJDIR)$(pathSeparator)main.o $(OBJDIR)$(pathSeparator)grid.o
	$(CC) $(CFLAG) $^ -o $(BUILDDIR)$(pathSeparator)$@ -lSDL2 -lSDL2main
	cp $(BUILDDIR)$(pathSeparator)$(NAME) $(NAME)

$(OBJDIR)$(pathSeparator)main.o : $(SRCDIR)$(pathSeparator)main.c
	$(CC) $(CFLAG) -c $^ -o $@

$(OBJDIR)$(pathSeparator)grid.o : $(SRCDIR)$(pathSeparator)grid.c
	$(CC) $(CFLAG) -c $^ -o $@



.PHONY : all clean init_folder

clean :
	-$(DEL_COMMAND) $(OBJDIR)$(pathSeparator)*
	-$(DEL_COMMAND) $(BUILDDIR)$(pathSeparator)$(NAME)
	-rmdir $(OBJDIR)
	-rmdir $(BUILDDIR)
	-$(DEL_COMMAND) $(NAME)
	-$(DEL_COMMAND) grid.txt

init_folder :
	-mkdir $(OBJDIR)
	-mkdir $(BUILDDIR)
