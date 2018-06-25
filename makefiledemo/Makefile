objects = main.o kbd.o command.o display.o \
		  insert.o search.o files.o utils.o
bar := e.mk f.mk
bar2 := ${bar:.mk=.o}

-include foo.make *.mk $(bar)
VPATH = src:../headers
all: edit main.o kbd.o command.o display.o insert.o search.o\
	files.o utils.o
.PHONY : all

edit: ${objects}
	cc -o edit ${objects}

main.o:  main.c defs.h
	@echo compiling main.c
	@echo ${bar2}
	echo $(word 2, foo bar baz)
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
	cc  -M -c utils.c 
	gcc -MM utils.c
exec:
	cd ~/; pwd
subsystem:
	cd subdir && $(MAKE)

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
