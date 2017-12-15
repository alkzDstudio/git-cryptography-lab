#include <iostream>
#include "Encoder.hpp"
#include "Decoder.hpp"
#include "Frequency_Table.hpp"
#include "Table_Frequency.hpp"


void main() {
	setlocale(0, "");

	int key;
	std::string name;
	int check = 0;
	char Gkey;
	std::cout << "Выберите операцию над файлом:" << std::endl;
	std::cout << "Зашифровать файл -> 0" << std::endl;
	std::cout << "Разшифровать файл -> 1" << std::endl;
	std::cout << "Частотный анализ -> 2" << std::endl;
	std::cin >> check;

	switch (check) {
	case (0): {
		int check_op = -1;
		Encoder obj;
		std::cout << "Введите название файла (пример: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "Сгенерировать ключ? Y/N" << std::endl;
		std::cin >> Gkey;
		if (Gkey == 'N' || Gkey == 'n') {
			std::cout << "Ввести ключ." << std::endl;
			std::cin >> key;
			check_op = obj.Encoder_object(name, key);
		}
		else {
			check_op = obj.Encoder_object(name);
		}

		if (check_op >= 0) {
			std::cout << "Операция прошла успешно." << std::endl;
			std::cout << "Зашифрованный файл называется: Encoder_" << name << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << "Ошибка. Операция не удалась!" << std::endl;

		break;
	}
	case (1): {
		Decoder obj;
		std::cout << "Введите название файла (пример: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "Введите ключ." << std::endl;
		std::cin >> key;
		int check_op = obj.Decoder_object(name, key);
		if (check_op >= 0) {
			std::cout << "Операция прошла успешно." << std::endl;
			std::cout << "Расшифрованный файл называется : Decoder_" << name << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << "Ошибка. Операция не удалась!" << std::endl;
		break;
	}
	case (2): {
		std::string a_name;
		std::cout << "Введите название файла для анализа частот (пример: name.txt)" << std::endl;
		std::cin >> a_name;
		Table_Frequency obj(a_name);
		std::cout << "Введите название файла для атаки (пример: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "key ("<< name <<") = " << obj.Key(name) << std::endl;
		
		break;
	}
	}

}