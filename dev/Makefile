.PHONY: all clean dep plot

all:
	cd src;  make
	cd test; make
	cd main; make

clean:
	cd src;  make clean
	cd test; make clean
	cd main; make clean
	cd plot; find . \
		-type f \
		-not -name "*.plt" \
		-not -name ".gitignore" \
		-not -name "doplots" \
		-delete

dep:
	cd src;  make dep
	cd test; make dep
	cd main; make dep

plot:
	cd plot; bash doplots
