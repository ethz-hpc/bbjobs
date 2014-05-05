CC := gcc

all: clean bbjobs install

bbjobs: bbjobs.o printer.o lsb_strings.o
	$(CC) -L${LSF_LIBDIR} -o bbjobs bbjobs.o printer.o lsb_strings.o -llsf -lbat -lnsl -lm

bbjobs.o: bbjobs.c bbjobs.h
	$(CC) -Wall -Os -I${LSF_LIBDIR}/../../include -c bbjobs.c -o bbjobs.o

printer.o: printer.c printer.h
	$(CC) -Wall -Os -c printer.c -o printer.o

lsb_strings.o: lsb_strings.c lsb_strings.h
	$(CC) -Wall -Os -I${LSF_LIBDIR}/../../include -c lsb_strings.c -o lsb_strings.o

clean:
	rm -f *.o bbjobs

install:
	cp bbjobs ${LSF_BINDIR}
