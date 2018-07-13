iterdir: iterdir.c ourhdr.c func.c
	cc -o iterdir.out -O2 iterdir.c ourhdr.c func.c
mycd: mycd.c ourhdr.c
	cc -o mycd.out -O2 mycd.c ourhdr.c
mygetcwd: mygetcwd.c ourhdr.c func.c
	cc -o mygetcwd.out -O2 mygetcwd.c ourhdr.c func.c
printdev: printdev.c ourhdr.c
	cc -o printdev.out -O2 printdev.c ourhdr.c
getpwname: getpwnam_demo.c
	cc -o getpwname.out -O2 getpwnam_demo.c
exit_demo: exit_demo.c ourhdr.c
	cc -o exit_demo.out -O2 exit_demo.c ourhdr.c
outcomm: outcomm.c ourhdr.c
	cc -o outcomm.out -O2 outcomm.c ourhdr.c 
jmp_demo: jmp_demo.c ourhdr.c
	cc -o jmp_demo1.out jmp_demo.c ourhdr.c
	cc -o jmp_demo2.out -O2 jmp_demo.c ourhdr.c
pr_lim: pr_limit.c ourhdr.c
	cc -o pr_lim.out -O2 pr_limit.c ourhdr.c


.PHONY: clean
clean:
	rm *.out
