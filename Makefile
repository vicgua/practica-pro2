.PHONY: all
all: main.o Almacen.o

.PHONY: clean
clean:
	@rm -rvf main.o Almacen.o

.PHONY: docs
docs:
	doxygen

.PHONY: latex
latex: docs
	$(MAKE) -C docs/latex