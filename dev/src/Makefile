include ../makeopts
SRC = $(shell ls *.cpp)

.PHONY: all clean dep

all: $(SRC:%.cpp=%.o)

clean:
	-rm .depend
	-rm *.o

dep:
	-$(CC) -MM $(SRC) > .depend

-include .depend

%.o: %.cpp
	$(CC) $(OP) -c $<
