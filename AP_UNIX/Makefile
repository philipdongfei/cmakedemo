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
system-demo: system-demo.c ystem.c ourhdr.c func.c 
	cc -o system-demo.out -O2 system-demo.c ystem.c func.c ourhdr.c 
tsys: tsys.c ${TOOL}
	cc -o tsys.out -O2 tsys.c ${TOOL}
prRealID: prRealID.c  ourhdr.c
	cc -o printuids.out -O2 prRealID.c ourhdr.c 
account-demo: account-demo.c ourhdr.c
	cc -o account-demo.out -O2 account-demo.c ourhdr.c
pr-account: pr-account.c ourhdr.c
	cc -o pr-account.out -O2 pr-account.c ourhdr.c
times-demo: times-demo.c ${TOOL} 
	cc -o times-demo.out -O2 times-demo.c ${TOOL} 
orphanedProcess: orphanedProcess.c ourhdr.c
	cc -o orphanedProcess.out -O2 orphanedProcess.c ourhdr.c
signal-simple: signal-simple.c ourhdr.h ourhdr.c
	cc -o signal-simple.out -O2 signal-simple.c ourhdr.h ourhdr.c
reentrant-demo: reentrant-demo.c ourhdr.h ourhdr.c
	cc -o reentrant-demo.out -O2 reentrant-demo.c ourhdr.c
sigcld-demo:  sigcld-demo.c 
	cc -o  sigcld-demo.out -O2 sigcld-demo.c 
do-sleep2: do-sleep2.c sleep2-demo.c ourhdr.c
	cc -o do-sleep2.out -O2 do-sleep2.c sleep2-demo.c ourhdr.c
read-time: read-time.c ourhdr.c
	cc -o read-time.out -O2 read-time.c ourhdr.c
read-demo: read-demo.c ourhdr.c
	cc -o read-demo.out -O2 read-demo.c ourhdr.c
sig_mask_demo: sig_mask_demo.c ourhdr.h ourhdr.c
	cc -o sig_mask_demo.out -O2 sig_mask_demo.c ourhdr.c
sig-jmp: sig-jmp.c sig_func.c ourhdr.h ourhdr.c
	cc -o sig-jmp.out -O2 sig-jmp.c sig_func.c ourhdr.c
sig-jmp-ex: sig-jmp-ex.c sig_func.c ourhdr.h ourhdr.c
	cc -o sig-jmp-ex.out -O2 sig-jmp-ex.c sig_func.c ourhdr.c
sigsuspend-demo: sigsuspend-demo.c sig_func.c ourhdr.h ourhdr.c
	cc -o sigsuspend-demo.out -O2 sigsuspend-demo.c sig_func.c ourhdr.c
sigsuspend-global: sigsuspend-global.c sig_func.c ourhdr.h ourhdr.c
	cc -o sigsuspend-global.out -O2 sigsuspend-global.c sig_func.c ourhdr.c
system-ed: system-ed.c ourhdr.c
	cc -o system-ed.out -O2 system-ed.c ourhdr.c
sigtstp-demo: sigtstp-demo.c ourhdr.h ourhdr.c
	cc -o sigtstp-demo.out  -O2 sigtstp-demo.c ourhdr.c
change-intr:  change-intr.c ourhdr.c
	cc -o change-intr.out -O2 change-intr.c ourhdr.c
tcgetattr-demo: tcgetattr-demo.c ourhdr.c
	cc -o tcgetattr-demo.out -O2 tcgetattr-demo.c ourhdr.c
test_isatty: test_isatty.c ourhdr.c
	cc -o test_isatty.out -O2 test_isatty.c ourhdr.c
test_ttyname: test_ttyname.c term-func.c ourhdr.c
	cc -o test_ttyname.out -O2 test_ttyname.c term-func.c ourhdr.c
getpass-demo: getpass-demo.c ourhdr.c
	cc -o getpass-demo.out  -O2 getpass-demo.c term-func.c ourhdr.c
sig-rawcb:    sig-raw-cbreak.c term-func.c ourhdr.c
	cc -o sig-rawcb.out -O2 sig-raw-cbreak.c term-func.c ourhdr.c
print-wnsz: print-size.c ourhdr.c
	cc -o print-winsz.out -O2 print-size.c ourhdr.c
nonblock-write: nonblock-write.c file-func.c ourhdr.c
	cc -o nonblock-write.out -O2 nonblock-write.c file-func.c ourhdr.c
deadlock-demo: deadlock-demo.c signal-sync.c lock-func.c ourhdr.c
	cc -o deadlock-demo.out -O2 deadlock-demo.c  signal-sync.c lock-func.c ourhdr.c
daemon-lock: daemon-lock.c lock-func.c ourhdr.c
	cc -o daemon-lock.out -O2 daemon-lock.c lock-func.c ourhdr.c
lck-file: lck-file.c lock-func.c ourhdr.c
	cc -o lck-file.out -O2 lck-file.c lock-func.c ourhdr.c
chk-lck: chk-lck.c signal-sync.c file-func.c lock-func.c ourhdr.c
	cc -o chk-lck.out -O2 chk-lck.c signal-sync.c file-func.c lock-func.c ourhdr.c
test-isastream: test-isastream.c stream-func.c ourhdr.h ourhdr.c
	cc -o test-isastream.out -O2 test-isastream.c stream-func.c ourhdr.c
pr-stream: pr-stream.c stream-func.c ourhdr.h ourhdr.c
	cc -o pr-stream.out -O2 pr-stream.c stream-func.c ourhdr.h ourhdr.c
getmsg-demo: getmsg-demo.c ourhdr.c 
	cc -o getmsg-demo.out -O2 getmsg-demo.c ourhdr.c
mmap-demo: mmap-demo.c ourhdr.h ourhdr.c
	cc -o mmap-demo.out -O2 mmap-demo.c ourhdr.c







.PHONY: clean
clean:
	rm *.out
