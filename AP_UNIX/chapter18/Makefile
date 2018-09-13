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
	
dial-client: client-main.c call.h call.c take.c cli_assist.c put.c doescape.c cli_loop.c \
	ourhdr.h ourhdr.c term-func.c cs_43pbsd.c proc_com_43pbds.c opend.c \
	io-func.c
	cc -o dial-client.out client-main.c call.h call.c take.c cli_assist.c put.c \
		doescape.c cli_loop.c ourhdr.c term-func.c cs_43pbsd.c proc_com_43pbds.c opend.c \
		io-func.c




.PHONY: clean
clean:
	rm *.out
