.PHONY : all clean rebuild genobj runtime

all:
	@make -C src
	@make -C test

clean:
	@make clean -C src
	@make clean -C test

rebuild: clean all

genobj:
	@make rebuild -C test

runtime:
	@make rebuild -C src
