#include "Table_Frequency.hpp"
#include <fstream>
#include <map>

void Table_Frequency::Filling_ASCII(char * alphabet) {
	for (int i = 0; i < size; i++) {
		alphabet[i] = i;
	}
}

Table_Frequency::Table_Frequency(const std::string & name) {
	Filling_ASCII(alphabet);
	
	std::ifstream file(name);
	if (!file) return;

	double tmp[256] = { 0 };
	char symbol = 0;
	int scope_symbole = 0;
	while (1) {
		scope_symbole++;
		file.get(symbol);
		if (file.eof()) break;
		for (int i = 0; i < size; i++) {
			if (alphabet[i] == symbol) {
				tmp[i]++;				
			}
		}
	}
	for (int i = 1; i < size; i++) {
		if (tmp[i] == 0)
			continue;
		FrequencyMap[tmp[i] / scope_symbole] = alphabet[i];
	}
}

int Table_Frequency::Key(const std::string & analysis) {
	int key = 0;
	Table_Frequency analysis_table(analysis);
	std::map<double, char>::iterator p1 = analysis_table.FrequencyMap.begin();

	for (; p1 != analysis_table.FrequencyMap.end(); p1++) {		
		for (std::map<double, char>::iterator p2 = FrequencyMap.begin(); p2 != FrequencyMap.end(); p2++) {
			if (((*p1).second - (*p2).second) < 0) {
				key = ((*p1).second - (*p2).second) + size - 1;
			}
			else {
				key = ((*p1).second - (*p2).second);
			}
		}		
	}
	return key;
}
