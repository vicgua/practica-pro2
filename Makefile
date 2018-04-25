.PHONY: all
all: main.o

.PHONY: clean
clean:
	@rm -rvf main.o

.PHONY: docs
docs:
	doxygen

.PHONY: latex
latex: docs
	$(MAKE) -C docs/latex