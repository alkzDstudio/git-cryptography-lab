#include "Frequency_Table.hpp"
#include <fstream>
#include <iostream>

void Frequency_Table::Filling_ASCII(char * alphabet) {
	for (int i = 0; i < size; i++)
		alphabet[i] = i;
}

int Frequency_Table::Maximum(int * array) {
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (max < array[i]) {
			max = array[i];
		}
	}
	return max;
}

Frequency_Table::Frequency_Table(const std::string & name){
	Filling_ASCII(alphabet);
	std::ifstream file(name);
	if (!file) return;
	int scope_symbole = 0;
	char symbole = 0;
	int tmp_table[256] = { 0 };
	while (1) {
		scope_symbole++;
		file.get(symbole);
		if (file.eof()) break;
		for (int i = 0; i < size; i++) {
			if (alphabet[i] == symbole) {
				tmp_table[i]++;
			}
		}
	}
	/*for (int t = 0; t < size - 1; t++) {
		std::cout << tmp_table[t] << " ";
	}*/
	bool tmp[256];
	int min = 0;
	int index = 0;
	int i = 0;
	int max = Maximum(tmp_table);
	while (1) {
		index = 0;
		min = max;
		for (int j = 0; j < size-1; j++) {
			if(tmp_table[j] == 0)
				tmp[j]= false;
			if (min >= tmp_table[j] && tmp[j]) {
				min = tmp_table[j];
				index = j;
			}
		}
		tmp[index] = false;
		for (int j = 0; j < size; j++) {
			if (!tmp[j])
				continue;
			table[j]++;
		}
		for (i = 0; i < size - 1; i++)
			if (tmp[i])
				break;
		if (i >= size - 1)
			break;
	}
	
	file.close();
}

int Frequency_Table::Key(const std::string & analysis) {	
	Frequency_Table analysis_table(analysis);
	/*for (int t = 0; t < size - 1; t++) {
		std::cout << table[t] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (int t = 0; t < size - 1; t++) {
		std::cout << analysis_table.table[t] << " ";
	}*/
	int key = 0;
	int tmp_table[511] = { 0 };
	int i = 0;
	int j = 0;
	int k = 0;
	int check = 0;
	int index = 0;
	int max = 0;
	for (i = 0; i < 2 * size - 2; i++) {
		if (i < size-1)
			tmp_table[i] = table[j++];
		else
			tmp_table[i] = table[k++];
	}
	
	for (i = 0, j = 0; i < 2 * size-2; i++) {
		for (k = i, j = 0, check = 0; j < size-1; j++, k++) {
			if (tmp_table[k] == analysis_table.table[j]) {
				check++;
			}
		}
		if (max < check) {
			max = check;
			key = i;
		}
	}	
	return key;
}
