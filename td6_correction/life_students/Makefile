all: all-redirect

MPICC   = mpicc
MPIEXEC = mpiexec
MPIEXEC_NP = -n
PNCDIR  = 
OMPFLAG = -fopenmp

# _XOPEN_SOURCE ensures that drand48 and friends are defined in stdlib.h
# _POSIX_C_SOURCE=199506L and HAVE_NANOSLEEP should be set if
# nanosleep is available
#CFLAGS+= -g -O0 -Wall -D_XOPEN_SOURCE -D_POSIX_C_SOURCE=199506L -DHAVE_NANOSLEEP
CFLAGS = -g -O2 -Drestrict=__restrict -DHAVE_DRAND48=1 -DHAVE_NANOSLEEP=1

STDOBJS= mlife.o mlife-io-stdout.o mlife-pt2pt.o
MPIOBJS= mlife.o mlife-io-mpiio.o mlife-pt2pt.o

.c.o:	$?
	$(MPICC) $(CFLAGS) -c $(?) -o $(@)
.f.o:   $?
	$(MPIF77) $(FFLAGS) -c $(?) -o $(@)

EXECS = mlife mlife-mpiio mlife-fence mlife-pscw mlife-fence-mpiio mlife-pscw-mpiio

default: mlife

all-redirect: $(EXECS)

mlife: $(STDOBJS)
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) $(STDOBJS) $(LIBS)

mlife-mpiio: $(MPIOBJS)
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) $(MPIOBJS) $(LIBS)

mlife-fence: mlife.o mlife-io-stdout.o mlife-fence.o
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) mlife.o mlife-io-stdout.o mlife-fence.o $(LIBS)

mlife-fence-mpiio: mlife.o mlife-io-mpiio.o mlife-fence.o
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) mlife.o mlife-io-mpiio.o mlife-fence.o $(LIBS)

mlife-pscw: mlife.o mlife-io-stdout.o mlife-pscw.o
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) mlife.o mlife-io-stdout.o mlife-pscw.o $(LIBS)

mlife-pscw-mpiio: mlife.o mlife-io-mpiio.o mlife-pscw.o
	$(MPICC) $(CFLAGS) -o $@ $(LDFLAGS) mlife.o mlife-io-mpiio.o mlife-pscw.o $(LIBS)
clean::
	rm -f *.o *.ps *.pdf $(EXECS) $(OMPEXECS) mlife-pnetcdf \
	mlife2d-fence mlife2d-fpmpi fpmpi_profile.txt *.chkpt *.exe *.stackdump

run: $(PROG)
	$(MPIEXEC) $(MPIEXEC_NP) $(NP) $(PROG) $(ARGS)
