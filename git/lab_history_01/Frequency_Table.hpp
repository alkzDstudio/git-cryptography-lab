#ifndef _FREQUENCY_TABLE_HPP_
#define _FREQUENCY_TABLE_HPP_
#include <string>

class Frequency_Table {
private:
	int table[256] = { 0 };
	char alphabet[256] = { 0 };
	int const size = 256;
	void Filling_ASCII(char * alphabet);
	int Maximum(int *array);
public:
	Frequency_Table(const std::string &name);
	int Key(const std::string &analysis);
};

#endif