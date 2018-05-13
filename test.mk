# Makefile for tests
PYTHON3 = python3

.PHONY: all public-tests custom-tests

all: public-tests custom-tests

public-tests: program.exe sample.inp sample.cor
	./program.exe < sample.inp | diff - sample.cor

custom-tests: program.exe custom.inp custom.cor
	./program.exe < custom.inp | diff - custom.cor

custom.inp custom.cor: testpp.py custom_tests/*
	$(PYTHON3) testpp.py -o custom custom_tests