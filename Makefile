CXX = g++
CXXFLAGS += -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Almacen.o Sala.o
	$(LINK.cc) -o $@ $^
program.o: program.cc Almacen.hh Sala.hh aux.hh BinTree.hh
Almacen.o: Almacen.cc Almacen.hh Sala.hh aux.hh BinTree.hh
Sala.o: Sala.cc Sala.hh aux.hh

practica.tar: Makefile program.cc Almacen.cc Almacen.hh Sala.cc Sala.hh aux.hh
	tar -cvf $@ $^

.PHONY: clean
clean:
	@rm -rvf main.o Almacen.o Sala.o program.o program.exe practica.tar

.PHONY: docs
docs:
	doxygen

.PHONY: latex
latex: docs
	$(MAKE) -C docs/latex

.PHONY: test
test: program.exe sample.inp sample.cor
	./program.exe < sample.inp | diff - sample.cor
