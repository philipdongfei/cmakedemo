iterdir: iterdir.c ourhdr.c func.c
	cc -o iterdir.out -O2 iterdir.c ourhdr.c func.c
mycd: mycd.c ourhdr.c
	cc -o mycd.out -O2 mycd.c ourhdr.c
mygetcwd: mygetcwd.c ourhdr.c func.c
	cc -o mygetcwd.out -O2 mygetcwd.c ourhdr.c func.c
printdev: printdev.c ourhdr.c
	cc -o printdev.out -O2 printdev.c ourhdr.c
getpwname: getpwnam_demo.c
	cc -o getpwname -O2 getpwnam_demo.c
.PHONY: clean
clean:
	rm *.out
