#include <iostream>
#include <fstream>


int main(int argc, char** argv) {

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <FileName>" << std::endl;
		return 0;
	}

	//Open the file for reading
	std::ifstream inFile(argv[1]);
	if (!inFile.good()) {
		std::cout << "Error Opening File!" << std::endl;
		return 1;
	}

	return 0;
}
