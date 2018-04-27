CXXFLAGS += -D_GLIBCXX_DEBUG -O0 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

.PHONY: all
all: main.o Almacen.o

main.o: main.cc Almacen.hh BinTree.hh Sala.hh
Almacen.o: Almacen.cc Almacen.hh BinTree.hh Sala.hh

.PHONY: clean
clean:
	@rm -rvf main.o Almacen.o

.PHONY: docs
docs:
	doxygen

.PHONY: latex
latex: docs
	$(MAKE) -C docs/latex
