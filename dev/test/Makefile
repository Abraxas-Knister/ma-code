include ../makeopts
SRC = $(shell ls *.cpp)

.PHONY: all clean dep

all: qbit.test qcrig.test

clean:
	-rm .depend
	-rm *.o
	-rm *.test

dep:
	-$(CC) -MM $(SRC) > .depend

-include .depend

qbit.test: qbit.o \
	../src/qbit.o

qcrig.test: qcrig.o \
	../src/qc.o \
	../src/gates.o

%.o: %.cpp
	$(CC) $(OP) -c $<

%.test:
	$(CC) $^ -o $@
