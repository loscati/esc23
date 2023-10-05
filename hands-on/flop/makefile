#
#  USAGE:
#     make          ... to build the programs
#     make test     ... to run the default test case
#

CC          = gcc-13
CPP         = g++-13
CLINKER     = $(CC)
CPPLINKER   = $(CPP)
#OPTFLAGS   = -std=c11 -fopenmp -O3
OPTFLAGS    = -O0 -fopenmp
LIBS        = -lm
CFLAGS	  = $(OPTFLAGS)

EXES = sum quad roundC roundCpp pi

all: $(EXES)

sum: sum.o
	$(CLINKER) $(OPTFLAGS) -o sum sum.o $(LIBS)

quad: quad.o
	$(CLINKER) $(OPTFLAGS) -o quad quad.o $(LIBS)

roundC: roundC.o
	$(CLINKER) $(OPTFLAGS) -o  roundC roundC.o $(LIBS)

roundCpp: roundCpp.o
	$(CPPLINKER) $(OPTFLAGS) -o  roundCpp roundCpp.o $(LIBS)

pi: pi.o
	$(CLINKER) $(OPTFLAGS) -o pi pi.o $(LIBS)

test: $(EXES)
	./sum
	./quad
	./roundC
	./roundCpp
	./pi

clean:
	rm -rf $(EXES) *.o

.SUFFIXES:
.SUFFIXES: .c .cc .o

.c.o:
	$(CC) $(CFLAGS) -c $<

.cc.o:
	$(CC) $(CFLAGS) -c $<
