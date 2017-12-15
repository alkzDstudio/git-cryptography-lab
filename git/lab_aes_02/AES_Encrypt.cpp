#include "AES_Encrypt.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))


AES_Encrypt::AES_Encrypt() {
}

int AES_Encrypt::Encrypt_object(const std::string & name, const std::string &key) {
	Nk = Nr / 32;
	Nr = Nk + 6;

	unsigned char temp[16] = { 0x00 };

	if (key == "") {
		std::cout << "Вы не ввели ключ, по этому система сгенерировала ключ: key = ";
		srand(time(NULL));
		for (int i = 0; i < 16; i++) {
			for (temp[i] = rand() % 127; temp[i] < 33; temp[i] = rand() % 127);
			std::cout << temp[i];
		}
		std::cout << std::endl;
	}
	else {
		for (int i = 0; i < 16 && i < key.length(); i++) {
			temp[i] = key[i];
		}
	}
	
	for (int i = 0;i < Nk * 4; i++)	{
		Key[i] = temp[i];
	}

	std::ifstream file (name, std::ios::in | std::ios::binary);
	if (!file) return -1;

	std::string name_id = "Encrypt_";
	name_id = name_id + name;

	std::ofstream EnFile(name_id, std::ios::out | std::ios::binary);
	if (!EnFile) return -1;

	char ch;
	char tmp[16];
	int i = 0;
	bool flag = false;
	while (1) {
		for (i = 0; i < 16; i++) {
			if (!file.get(ch)) {
				in[i] = 0;
				flag = true;
			}
			else
				in[i] = ch;
		}
		KeyExpansion();
		Cipher();
		for (i = 0; i < 16; i++) {
			tmp[i] = out[i];
		}
		EnFile.write(tmp, 16);
		if (flag) {
			break;
		}
	}

	file.close();
	EnFile.close();

	return 0;
}

void AES_Encrypt::KeyExpansion() {
	int i, j;
	unsigned char temp[4], k;

	for (i = 0; i < Nk; i++) {
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}

	while (i < (Nb * (Nr + 1))) {
		for (j = 0; j < 4; j++)	{
			temp[j] = RoundKey[(i - 1) * 4 + j];
		}
		if (i % Nk == 0) {
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}
			{
				temp[0] = getSBoxValue(temp[0]);
				temp[1] = getSBoxValue(temp[1]);
				temp[2] = getSBoxValue(temp[2]);
				temp[3] = getSBoxValue(temp[3]);
			}
			temp[0] = temp[0] ^ Rcon[i / Nk];

		} else if (Nk > 6 && i % Nk == 4) {
			{
				temp[0] = getSBoxValue(temp[0]);
				temp[1] = getSBoxValue(temp[1]);
				temp[2] = getSBoxValue(temp[2]);
				temp[3] = getSBoxValue(temp[3]);
			}
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp[3];
		i++;
	}
}

void AES_Encrypt::AddRoundKey(int round) {
	int i, j;
	for (i = 0;i < 4; i++) {
		for (j = 0;j < 4; j++)	{
			state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
}

void AES_Encrypt::SubBytes() {
	int i, j;
	for (i = 0; i < 4; i++)	{
		for (j = 0; j < 4; j++)	{
			state[i][j] = getSBoxValue(state[i][j]);
		}
	}
}

void AES_Encrypt::ShiftRows() {
	unsigned char temp;

	temp = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = temp;

	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	temp = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = temp;
}

void AES_Encrypt::MixColumns() {
	int i;
	unsigned char Tmp, Tm, t;
	for (i = 0; i < 4; i++)
	{
		t = state[0][i];
		Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
		Tm = state[0][i] ^ state[1][i]; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp;
		Tm = state[1][i] ^ state[2][i]; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp;
		Tm = state[2][i] ^ state[3][i]; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp;
		Tm = state[3][i] ^ t; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp;
	}
}

void AES_Encrypt::Cipher() {
	int i, j, round = 0;

	for (i = 0; i < 4; i++)	{
		for (j = 0; j < 4; j++)	{
			state[j][i] = in[i * 4 + j];
		}
	}
	AddRoundKey(0);

	for (round = 1;round < Nr; round++) {
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}

	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)	{
			out[i * 4 + j] = state[j][i];
		}
	}	
}

