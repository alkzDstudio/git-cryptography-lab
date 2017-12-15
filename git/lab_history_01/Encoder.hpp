#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_
#include <string>

class Encoder {
private:
	char alphabet[256] = { 0 };
	int const size = 256;
	void Filling_ASCII(char * alphabet);
	int key = 0;
public:	
	Encoder();
	int Encoder_object(const std::string &name, int const iskey = 0);
};

#endif