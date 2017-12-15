#include "Encoder.hpp"
#include <fstream>
#include <random>
#include <iostream>
#include <ctime>

void Encoder::Filling_ASCII(char * alphabet) {
	for (int i = 0; i < size; i++)
		alphabet[i] = i;
}

Encoder::Encoder(){
	Filling_ASCII(alphabet);
}


int Encoder::Encoder_object(const std::string & name, int const iskey) {
	key = iskey;
	srand(time(NULL));
	if (key == 0) {
		key = 1 + rand() % 254;
		std::cout << "key = " << key << std::endl;
	}
	std::ifstream file(name);
	if (!file) return -1;

	std::string name_id = "Encoder_";
	name_id = name_id + name;
	
	std::ofstream EnFile(name_id);
	if (!EnFile) return -1;

	char symbol;
	char encoderSymbol;
	while (1) {
		if (!file.get(symbol)) break;
		for (int i = 0; i < size; i++) {
			if (alphabet[i] == symbol) {
				encoderSymbol = alphabet[(i + key) % (size - 1)];
				EnFile << encoderSymbol;
				break;
			}
		}
	}
	file.close();
	EnFile.close();
	return 0;
}
