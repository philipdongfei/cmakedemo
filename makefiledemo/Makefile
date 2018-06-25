objects = main.o kbd.o command.o display.o \
		  insert.o search.o files.o utils.o
bar = e.mk f.mk

-include foo.make *.mk $(bar)
VPATH = src:../headers
all: edit main.o kbd.o command.o display.o insert.o search.o\
	files.o utils.o
.PHONY : all

edit: $(objects)
	cc -o edit $(objects)

main.o:  defs.h
	cc -c main.c
kbd.o:  defs.h command.h
	cc -c kbd.c
command.o:  defs.h command.h
	cc -c command.c
display.o:  defs.h buffer.h
	cc -c display.c
insert.o:  defs.h buffer.h
	cc -c insert.c
search.o:  defs.h buffer.h
	cc -c search.c
files.o:  defs.h buffer.h command.h
	cc -c files.c
utils.o:  defs.h
	cc -c utils.c 
.PHONY: clean cleanobj cleandiff 
clean:
	-rm edit $(objects)
	-rm *.o temp
cleanall: cleanobj cleandiff
	-rm edit
cleanobj:
	rm *.o
cleandiff:
	rm *.diff
