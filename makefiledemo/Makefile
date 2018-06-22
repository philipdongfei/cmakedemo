objects = main.o kbd.o command.o display.o \
		  insert.o search.o files.o utils.o

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
.PHONY: clean
clean:
	rm edit $(objects)
