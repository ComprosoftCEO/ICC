# Makefile for Insanity C Compiler



all: Insanity.out

Insanity.out: insanity.tab.cpp insanity.yy.cpp Statement/CommandToCode.cpp Statement/LabelToCode.cpp
	g++ -std=c++11 $^ -o $@

# Build the parser (using a Bison file)
%.tab.cpp: %.y
	bison -d -o $@ $<

# Build the lexer (using a Flex file)
%.yy.cpp: %.l
	flex -o $@ $<



# Run the file
.PHONY: run
run: Insanity.out
	./Insanity.out

# Remove all files
.PHONY: clean
clean:
	rm -f Insanity.out
	rm -f insanity.tab.cpp insanity.yy.cpp insanity.tab.hpp
