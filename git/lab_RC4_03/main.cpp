#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>

unsigned char s[256];
unsigned int i, j;
char *memblock;
char *enblock;
void swap(unsigned char *s, unsigned int i, unsigned int j) {
	unsigned char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}
void rc4_input(unsigned char *pass, unsigned int keylen) {
	for (i = 0; i < 256; i++)
		s[i] = i;
	for (i = 0, j = 0; i < 256; i++) {
		j = (j + pass[i % keylen] + s[i]) % 256;
		swap(s, i, j);
	}
	i = 0;
	j = 0;
}
unsigned char rc4_output() {
	i = (i + 1) % 256;
	j = (j + s[i]) % 256;
	swap(s, i, j);
	return s[(s[i] + s[j]) % 256];
}
int main() {
	setlocale(0, "");
	int size;	
	unsigned char* key[16] = { (unsigned char*)"key" };

	// создаем поток ключей
	rc4_input(key[0], strlen((char*)key[0]));
	//открытый текст в 'Alice.txt'
	std::ifstream original("Alice.txt", std::ios::in | std::ios::ate);
	// размер файла
	size = (int)original.tellg();

	// выделяем память для хранения данных
	memblock = new char[size];
	enblock = new char[size];
	original.seekg(0, std::ios::beg);
	// хранить открытый текст в памяти
	original.read(memblock, size);
	original.close();

	std::cout << std::endl;
	std::cout << "------------------------   ЗАШИФРОВАННЫЙ ТЕКСТ   ------------------------" << std::endl;	
	std::cout << std::endl;
	//Зашифровываем
	for (int i = 0; i < size; i++) {
		enblock[i] = (memblock[i] ^ rc4_output());
		std::cout << enblock[i];
	}
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------   РАСШИФРОВАННЫЙ ТЕКСТ   ------------------------" << std::endl;
	std::cout << std::endl;

	rc4_input(key[0], strlen((char*)key[0]));
	//Дешифруем
	for (int i = 0; i < size; i++) {
		enblock[i] = (enblock[i] ^ rc4_output());
		std::cout << enblock[i];
	}
	std::cout << std::endl;
	
	delete[] memblock;
	delete[] enblock;
	return 0;
}