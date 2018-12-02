# Makefile for Insanity C Compiler
CC=g++
CFLAGS=-std=c++11

PROGRAM=Insanity.out

OBJECTS=\
	insanity.tab.o \
	insanity.yy.o \
	InsanityProgram.o \
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
run: Insanity.out
	./Insanity.out

# Remove all files
.PHONY: clean
clean:
	rm -f $(PROGRAM) $(OBJECTS)
	rm -f insanity.tab.cpp insanity.yy.cpp
