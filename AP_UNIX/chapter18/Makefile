TOOL := ourhdr.h ourhdr.c func.c system-func.c


dial-demo: main.c calld.h childdial.c cliargs.c client.c ctlstr.c debug.c devfile.c dialfile.c\
	expectstr.c lock.c loop.c request.c sendstr.c sigchld.c sysfile.c ttydial.c ttyopen.c
	cc -o dial-demo.out -O2  main.c calld.h childdial.c cliargs.c client.c ctlstr.c debug.c \
	devfile.c dialfile.c expectstr.c lock.c loop.c request.c sendstr.c sigchld.c \
	sysfile.c ttydial.c ttyopen.c


.PHONY: clean
clean:
	rm *.out
