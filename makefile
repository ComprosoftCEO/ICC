# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11 -IInclude

PROGRAM=icc.out

OBJECTS=\
	insanity.tab.o \
	insanity.yy.o \
	ICC.o \
	InsanityProgram.o \
	CodeSegments.o \
	Statement/Statement.o \
	Statement/CommandStatement.o \
	Statement/LabelStatement.o \
	Statement/JumpStatement.o \
	Statement/SubroutineStatement.o \
	Statement/LibraryCallStatement.o \
	Statement/IfStatement.o \
	Statement/StatementList.o


all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Build the parser (using a Bison file)
%.tab.o: %.tab.cpp
%.tab.cpp: %.y
	bison -d -o $@ $<

# Build the lexer (using a Flex file)
%.yy.o: %.yy.cpp
%.yy.cpp: %.l
	flex -o $@ $<



# Run the file
.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

# Remove all files
.PHONY: clean
clean:
	rm -f $(PROGRAM) $(OBJECTS)
	rm -f insanity.tab.cpp insanity.yy.cpp insanity.tab.hpp
