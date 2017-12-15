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
	std::cout << "�������� �������� ��� ������:" << std::endl;
	std::cout << "����������� ���� -> 0" << std::endl;
	std::cout << "������������ ���� -> 1" << std::endl;
	std::cin >> check;

	switch (check) {
		case (0): {
			int check_op = -1;
			AES_Encrypt obj;
			std::cout << "������� �������� ����� (������: name.txt)" << std::endl;
			std::cin >> name;
			std::cout << "������������� ����? Y/N" << std::endl;
			std::cin >> Gkey;
			if (Gkey == 'N' || Gkey == 'n') {
				std::cout << "������ ���� (������ ����� �������� 16 ��������)" << std::endl;
				std::cin >> key;
				check_op = obj.Encrypt_object(name, key);
			} else {
				check_op = obj.Encrypt_object(name);
			}	
			
			if (check_op >= 0) {
				std::cout << "�������� ������ �������." << std::endl;
				std::cout << "������������� ���� ����������: Encrypt_" << name << std::endl;
				std::cout << std::endl;
			} else 
				std::cout << "������. �������� �� �������!" << std::endl;
			
			break;
		}
		case (1): {
			AES_Decrypt obj;
			std::cout << "������� �������� ����� (������: name.txt)" << std::endl;
			std::cin >> name;
			std::cout << "������� ���� �� ������� 16 ��������" << std::endl;
			std::cin >> key;
			int check_op = obj.Decrypt_object(name, key);
			if (check_op >= 0) {
				std::cout << "�������� ������ �������." << std::endl;
				std::cout << "�������������� ���� ���������� : Decrypt_" << name << std::endl;
				std::cout << std::endl;
			} else
				std::cout << "������. �������� �� �������!" << std::endl;
			break;
		}			  
	}
}