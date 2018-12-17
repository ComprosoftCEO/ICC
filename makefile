# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11 -Iinclude

PROGRAM=icc.out

OBJECTS=\
	Parser/insanity.tab.o \
	Parser/insanity.yy.o \
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

# Add the source directory
OBJECTS := $(OBJECTS:%=src/%)



all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Build the parser (using a Bison file)
%.tab.o: %.tab.cpp
%.tab.cpp: %.y
	bison --defines=$(@:%.cpp=%.h) -o $@ $<

# Build the lexer (using a Flex file)
%.yy.o: %.yy.cpp
%.yy.cpp: %.l
	flex --header-file=$(@:%.cpp=%.h) -o $@ $<



# Run the file
.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM)

# Remove all files
.PHONY: clean
clean:
	rm -f $(PROGRAM) $(OBJECTS)
	rm -f src/parser/insanity.tab.cpp src/parser/insanity.yy.cpp
	rm -f src/parser/insanity.tab.h src/parser/insanity.yy.h
