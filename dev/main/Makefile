include ../makeopts
SRC = $(shell ls *.cpp)

.PHONY: all clean dep

all: main.prog

clean:
	-rm .depend
	-rm *.o
	-rm *.prog

dep:
	-$(CC) -MM $(SRC) > .depend

-include .depend

main.prog: main.o \
	../src/fourier.o \
	../src/twosite.o \
	../src/dense-ed.o \
	../src/util.o \
	../src/random.o \
	../src/gates.o \
	../src/qc.o \
	../src/qmeth.o \

%.o: %.cpp
	$(CC) $(OP) -c $<

%.prog:
	$(CC) -fopenmp -o $@ $^
