CC = g++
OP = -I $(PWD)/src -pedantic-errors -fmax-errors=5 -Wall -Wextra -std=c++17 -O3 -march=native -fopenmp
SRC = $(shell ls src/*.cpp)
OBJ = $(SRC:%.cpp=%.o)
MN = $(shell ls main/*.hpp)
DEPFILE = .depend

.PHONY: all clean dep test plot
.PRECIOUS: %.o

all: $(MN:%.hpp=%.prog)

clean:
	-rm main/*.prog
	-rm src/*.o

dep:
	-$(CC) -MM -I $(PWD)/src $(SRC) > $(DEPFILE)

-include $(DEPFILE)
%.o: %.cpp
	$(CC) $(OP) -c $< 
	-mv *.o src/

%.prog: %.hpp $(OBJ)
	echo '#include "'$<'"' > main.cpp
	$(CC) $(OP) $(OBJ) main.cpp -o $@
	rm main.cpp

test: $(SRC)
	$(CC) $(OP) $(OBJ) test/qbit.cpp -o test/qbit.test
	$(CC) $(OP) $(OBJ) test/qcrig.cpp -o test/qcrig.test

plot:
	cd plot ;\
	./mat.plt
