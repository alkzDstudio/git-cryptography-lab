#ifndef _TABLE_FREQUENCY_HPP_
#define _TABLE_FREQUENCY_HPP_
#include <string>
#include <map>

class Table_Frequency {
private:
	char alphabet[256] = { 0 };
	int const size = 256;
	void Filling_ASCII(char * alphabet);
	std::map<double,char> FrequencyMap;
public:
	Table_Frequency(const std::string &name);
	int Key(const std::string &analysis);
};

#endif