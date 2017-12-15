#include <string>
#include <iostream>
#include "AES_Encrypt.hpp"
#include "AES_Decrypt.hpp"

void main() {
	setlocale(0, "");
	std::string key;
	std::string name;
	int check = 0;
	char Gkey;
	std::cout << "Выберите операцию над файлом:" << std::endl;
	std::cout << "Зашифровать файл -> 0" << std::endl;
	std::cout << "Разшифровать файл -> 1" << std::endl;
	std::cin >> check;

	switch (check) {
		case (0): {
			int check_op = -1;
			AES_Encrypt obj;
			std::cout << "Введите название файла (пример: name.txt)" << std::endl;
			std::cin >> name;
			std::cout << "Сгенерировать ключ? Y/N" << std::endl;
			std::cin >> Gkey;
			if (Gkey == 'N' || Gkey == 'n') {
				std::cout << "Ввести ключ (размер ключа небольше 16 символов)" << std::endl;
				std::cin >> key;
				check_op = obj.Encrypt_object(name, key);
			} else {
				check_op = obj.Encrypt_object(name);
			}	
			
			if (check_op >= 0) {
				std::cout << "Операция прошла успешно." << std::endl;
				std::cout << "Зашифрованный файл называется: Encrypt_" << name << std::endl;
				std::cout << std::endl;
			} else 
				std::cout << "Ошибка. Операция не удалась!" << std::endl;
			
			break;
		}
		case (1): {
			AES_Decrypt obj;
			std::cout << "Введите название файла (пример: name.txt)" << std::endl;
			std::cin >> name;
			std::cout << "Введите ключ из неболее 16 символов" << std::endl;
			std::cin >> key;
			int check_op = obj.Decrypt_object(name, key);
			if (check_op >= 0) {
				std::cout << "Операция прошла успешно." << std::endl;
				std::cout << "Расшифрованный файл называется : Decrypt_" << name << std::endl;
				std::cout << std::endl;
			} else
				std::cout << "Ошибка. Операция не удалась!" << std::endl;
			break;
		}			  
	}
}