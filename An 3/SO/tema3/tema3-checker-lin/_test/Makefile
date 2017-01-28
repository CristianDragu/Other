#CPPFLAGS = -DDEBUG -DLOG_LEVEL=LOG_DEBUG
CFLAGS = -Wall -g -Wno-unused

.PHONY: all clean test

all: run_test.o vmsim_test_lin.o common_lin.o vmsim_test.o vmsim.o
	gcc -shared vmsim.o -o libvmsim.so; cp libvmsim.so ../

run_test.o: run_test.c run_test.h vmsim_test.h
	gcc -c -fpic run_test.c -o run_test.o

vmsim_test_lin.o: vmsim_test_lin.c common.h
	gcc -c -fpic vmsim_test_lin.c

common_lin.o: common_lin.c common.h util.h debug.h
	gcc -c -fpic common_lin.c

vmsim_test.o: vmsim_test.c run_test.h vmsim.h vmsim_aux.h debug.h
	gcc -c -fpic vmsim_test.c

vmsim.o: vmsim.c vmsim.h
	gcc -c -fpic vmsim.c -o vmsim.o

clean:
	-rm -f *~ *.o