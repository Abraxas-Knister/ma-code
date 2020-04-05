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
	../src/green.o \
	../src/setup.o \
	../src/util.o

%.o: %.cpp
	$(CC) $(OP) -c $<

%.prog:
	$(CC) $^ -o $@
