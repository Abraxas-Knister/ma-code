include ../makeopts
SRC = $(shell ls *.cpp)

.PHONY: all clean dep

all: fourier.test qbit.test qcrig.test random.test

clean:
	-rm .depend
	-rm *.o
	-rm *.test

dep:
	-$(CC) -MM $(SRC) > .depend

-include .depend

fourier.test: fourier.o \
	../src/util.o \
	../src/fourier.o

qbit.test: qbit.o \
	../src/qbit.o

qcrig.test: qcrig.o \
	../src/qc.o \
	../src/gates.o \
	../src/random.o

random.test: random.o \
	../src/random.o

%.o: %.cpp
	$(CC) $(OP) -c $<

%.test:
	$(CC) $^ -o $@
