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

$(NAME) : $(OBJDIR)$(pathSeparator)main.o $(OBJDIR)$(pathSeparator)grid.o $(OBJDIR)$(pathSeparator)draw_texture.o
	$(CC) $(CFLAG) $^ -o $(BUILDDIR)$(pathSeparator)$@ -lSDL2 -lSDL2main
	cp $(BUILDDIR)$(pathSeparator)$(NAME) $(NAME)
	echo 10 10 500 > grid.txt
	echo 0 0 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 0 1 0 0 0 0 0 0 0 >> grid.txt
	echo 0 0 0 1 1 0 0 0 0 0 >> grid.txt
	echo 0 0 1 1 0 0 0 0 0 0 >> grid.txt
	echo 0 0 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 0 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 1 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 1 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 1 0 0 0 0 0 0 0 0 >> grid.txt
	echo 0 0 0 0 0 0 0 0 0 0 >> grid.txt

$(OBJDIR)$(pathSeparator)main.o : $(SRCDIR)$(pathSeparator)main.c
	$(CC) $(CFLAG) -c $^ -o $@

$(OBJDIR)$(pathSeparator)grid.o : $(SRCDIR)$(pathSeparator)grid.c
	$(CC) $(CFLAG) -c $^ -o $@

$(OBJDIR)$(pathSeparator)draw_texture.o : $(SRCDIR)$(pathSeparator)draw_texture.c
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
