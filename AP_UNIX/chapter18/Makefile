TOOL := ourhdr.h ourhdr.c func.c system-func.c


dial-server: server-main.c calld.h childdial.c cliargs.c client.c ctlstr.c debug.c devfile.c dialfile.c\
	expectstr.c lock.c loop.c request.c sendstr.c sigchld.c sysfile.c ttydial.c ttyopen.c log-daemon.c \
	cs_43pbsd.c	pipe-func.c ourhdr.c func.c system-func.c daemon-func.c file-func.c proc_com_43pbds.c\
	sig_func.c opend.h opend.c io-func.c sleepus.c
	cc -o dial-demo.out -O2  server-main.c calld.h childdial.c cliargs.c client.c ctlstr.c debug.c \
	devfile.c dialfile.c expectstr.c lock.c loop.c request.c sendstr.c sigchld.c \
	sysfile.c ttydial.c ttyopen.c log-daemon.c cs_43pbsd.c pipe-func.c ourhdr.c func.c \
	system-func.c daemon-func.c file-func.c proc_com_43pbds.c sig_func.c opend.h opend.c io-func.c \
	sleepus.c



.PHONY: clean
clean:
	rm *.out
