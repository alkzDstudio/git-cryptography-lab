#include "Decoder.hpp"
#include <fstream>

void Decoder::Filling_ASCII(char * alphabet) {
	for (int i = 0; i < size; i++)
		alphabet[i] = i;
}

Decoder::Decoder(){
	Filling_ASCII(alphabet);
}

int Decoder::Decoder_object(const std::string & name, int const key) {
	std::ifstream file(name);
	if (!file) return -1;

	std::string name_id = "Decoder_";
	name_id = name_id + name;

	std::ofstream DeFile(name_id);
	if (!DeFile) return -1;
	int tmp_key = key % (size - 1);
	char symbol;
	char encoderSymbol;
	while (1) {
		if (!file.get(symbol)) break;

		for (int i = 0; i < size; i++) {
			if (alphabet[i] == symbol) {
				if ((i - tmp_key) < 0) {
					encoderSymbol = alphabet[i - tmp_key + size - 1];
				}
				else {
					encoderSymbol = alphabet[i - tmp_key];
				}
				DeFile << encoderSymbol;
				break;
			}
		}
	}
	file.close();
	DeFile.close();
	return 0;
}
