CXX = g++
CXXFLAGS += -D_GLIBCXX_DEBUG -O0 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

.PHONY: all
all: practica.exe

practica.exe: main.o Almacen.o Sala.o
	$(LINK.cc) -o $@ $^
main.o: main.cc Almacen.hh BinTree.hh Sala.hh
Almacen.o: Almacen.cc Almacen.hh BinTree.hh Sala.hh
Sala.o: Sala.cc Sala.hh

.PHONY: clean
clean:
	@rm -rvf main.o Almacen.o Sala.o practica.exe

.PHONY: docs
docs:
	doxygen

.PHONY: latex
latex: docs
	$(MAKE) -C docs/latex

.PHONY: test
test: practica.exe sample.inp sample.cor
	./practica.exe < sample.inp