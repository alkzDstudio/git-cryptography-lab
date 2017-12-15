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
	std::cout << "�������� �������� ��� ������:" << std::endl;
	std::cout << "����������� ���� -> 0" << std::endl;
	std::cout << "������������ ���� -> 1" << std::endl;
	std::cout << "��������� ������ -> 2" << std::endl;
	std::cin >> check;

	switch (check) {
	case (0): {
		int check_op = -1;
		Encoder obj;
		std::cout << "������� �������� ����� (������: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "������������� ����? Y/N" << std::endl;
		std::cin >> Gkey;
		if (Gkey == 'N' || Gkey == 'n') {
			std::cout << "������ ����." << std::endl;
			std::cin >> key;
			check_op = obj.Encoder_object(name, key);
		}
		else {
			check_op = obj.Encoder_object(name);
		}

		if (check_op >= 0) {
			std::cout << "�������� ������ �������." << std::endl;
			std::cout << "������������� ���� ����������: Encoder_" << name << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << "������. �������� �� �������!" << std::endl;

		break;
	}
	case (1): {
		Decoder obj;
		std::cout << "������� �������� ����� (������: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "������� ����." << std::endl;
		std::cin >> key;
		int check_op = obj.Decoder_object(name, key);
		if (check_op >= 0) {
			std::cout << "�������� ������ �������." << std::endl;
			std::cout << "�������������� ���� ���������� : Decoder_" << name << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << "������. �������� �� �������!" << std::endl;
		break;
	}
	case (2): {
		std::string a_name;
		std::cout << "������� �������� ����� ��� ������� ������ (������: name.txt)" << std::endl;
		std::cin >> a_name;
		Table_Frequency obj(a_name);
		std::cout << "������� �������� ����� ��� ����� (������: name.txt)" << std::endl;
		std::cin >> name;
		std::cout << "key ("<< name <<") = " << obj.Key(name) << std::endl;
		
		break;
	}
	}

}