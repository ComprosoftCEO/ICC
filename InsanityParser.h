#ifndef INSANITY_PARSER_HEADER
#define INSANITY_PARSER_HEADER

#include <fstream>
#include <vector>
#include <map>

//All types of commands
enum class CommandType {
	NORMAL_COMMAND,
	JUMP,
	SUBROUTINE,
	IF_STATEMENT
};


//Single Insanity Command
struct Command {
	char command;
	CommandType type;
	std::string label;
	std::vector<Command*> subCommands;
	Command* parent;

public:
	Command();
	~Command();
};


// Entire insanity program
class InsanityProgram {

private:
	std::vector<Command*> program;
	std::map<std::string, size_t> labels;
	std::vector<Command*> unresolvedLabels;
	bool isLibrary;


private:

	//Construct a new Insanity Program
	InsanityProgram(bool isLibrary);

	//Adding tokens to the Insanity program
	void addCommand(char command);

	bool addLabel(std::string label);
	void addJump(std::string jump);
	void addSubroutine(std::string jump);
	void addLibraryCall(std::string jump);

	void insertIf();
	void exitIf();


public:
	~InsanityProgram();

	static InsanityProgram* readProgram(bool isLibrary, std::ifstream file);
	void printError();
};

#endif
