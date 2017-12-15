#ifndef _DECODER_HPP_
#define _DECODER_HPP_
#include <string>

class Decoder {
private:
	char alphabet[256] = { 0 };
	int const size = 256;
	void Filling_ASCII(char * alphabet);
public:
	Decoder();
	int Decoder_object(const std::string &name, int const key);
};

#endif