# Makefile for Insanity C Compiler

all: Insanity.out

Insanity.out: insanity.tab.c insanity.yy.c
	gcc $^ -o $@

%.tab.c: %.y
	bison -d -o $@ $<

%.yy.c: %.l
	flex -o $@ $<



# Run the file
.PHONY: run
run: Insanity.out
	./Insanity.out

# Remove all files
.PHONY: clean
clean:
	rm -f Insanity.out
	rm -f insanity.tab.c insanity.yy.c insanity.tab.h
