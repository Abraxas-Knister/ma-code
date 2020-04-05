.PHONY: all clean dep plot

all:
	cd src;  make
	cd test; make
	cd main; make

clean:
	cd src;  make clean
	cd test; make clean
	cd main; make clean

dep:
	cd src;  make dep
	cd test; make dep
	cd main; make dep

plot:
	cd plot; ./mat.plt
