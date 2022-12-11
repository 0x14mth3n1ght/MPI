all: all-redirect

MPICC   = mpicc
MPIEXEC = mpirun
MPIEXEC_NP = -n

CFLAGS = -g -O2 -Drestrict=__restrict -DHAVE_DRAND48=1 -DHAVE_NANOSLEEP=1

STDOBJS= mlife.o mlife-io-stdout.o mlife-pt2pt.o
MPIOBJS= mlife.o mlife-io-mpiio.o mlife-pt2pt.o

.c.o:	$?
	$(MPICC) $(CFLAGS) -c $(?) -o $(@)

EXECS = mlife mlife-mpiio

default: mlife

all-redirect: $(EXECS)

mlife: $(STDOBJS)
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) $(STDOBJS) $(LIBS)

mlife-mpiio: $(MPIOBJS)
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) $(MPIOBJS) $(LIBS)

clean::
	rm -f *.o $(EXECS) \
	*.chkpt

run: $(PROG)
	$(MPIEXEC) $(MPIEXEC_NP) $(NP) $(PROG) $(ARGS)
