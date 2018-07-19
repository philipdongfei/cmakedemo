TOOL := ourhdr.h ourhdr.c func.c system-func.c

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
fork_demo: fork_demo.c ourhdr.c
	cc -o fork_demo.out -O2 fork_demo.c ourhdr.c
vfork-demo: vfork-demo.c ourhdr.c
	cc -o vfork-demo.out -O2 vfork-demo.c ourhdr.c
exit-demo: exit-demo.c ${TOOL}
	cc -o exit-demo.out -O2 exit-demo.c ${TOOL}
double-fork: double-fork.c ${TOOL}
	cc -o double-fork.out -O2 double-fork.c ourhdr.c
race-fork: race-fork ${TOOL}
	cc -o race-fork.out -O2 race-fork.c ourhdr.h ourhdr.c
exec-demo: echoall.c exec-demo.c ourhdr.c
	cc -o echoall.out -O2 echoall.c ourhdr.c
	sudo mv echoall.out /home/philip/bin
	cc -o exec-demo.out -O2 exec-demo.c ourhdr.c
parser-demo: parser-demo.c ourhdr.c
	cc -o parser-demo.out -O2 parser-demo.c ourhdr.c
system-demo: system-demo.c system-func.c ${TOOL}
	cc -o system-demo.out -O2 system-demo.c system-func.c ${TOOL}
tsys: tsys.c ${TOOL}
	cc -o tsys.out -O2 tsys.c ${TOOL}
prRealID: prRealID.c  ourhdr.c
	cc -o printuids.out -O2 prRealID.c ourhdr.c 
account-demo: account-demo.c ourhdr.c
	cc -o account-demo.out -O2 account-demo.c ourhdr.c


.PHONY: clean
clean:
	rm *.out
