.PHONY : all clean rebuild

all:
	@make -C src
	@make -C test

clean:
	@make clean -C src
	@make clean -C test

rebuild: clean all
