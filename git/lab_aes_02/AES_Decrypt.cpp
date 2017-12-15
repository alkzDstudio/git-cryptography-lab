#include "AES_Decrypt.hpp"
#include <string>
#include <fstream>

#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

AES_Decrypt::AES_Decrypt() {
}

int AES_Decrypt::Decrypt_object(const std::string & name, const std::string &key) {
	Nk = Nr / 32;
	Nr = Nk + 6;
	
	unsigned char temp[16] = { 0x00 };
	for (int i = 0; i < 16 && i < key.length(); i++) {
		temp[i] = key[i];
	}

	for (int i = 0;i < Nk * 4; i++) {
		Key[i] = temp[i];
	}

	std::ifstream file(name, std::ios::in | std::ios::binary);
	if (!file) return -1;

	std::string name_id = "Decrypt_";
	name_id = name_id + name;

	std::ofstream DeFile(name_id, std::ios::out | std::ios::binary);
	if (!DeFile) return -1;

	char ch[16];
	int i = 0;
	while (file.read(ch, 16)) {
		for (i = 0; i < 16; i++) {
			in[i] = ch[i];
		}
		KeyExpansion();
		InvCipher();
		for (i = 0; i < 16; i++) {
			ch[i] = out[i];
		}
		DeFile.write(ch, 16);
	}

	file.close();
	DeFile.close();

	return 0;
}

void AES_Decrypt::KeyExpansion() {
	int i = 0;
	int j = 0;
	unsigned char temp1[4] = { 0 };
	unsigned char k = 0;

	for (i = 0; i < Nk; i++) {
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}
	
	while (i < (Nb * (Nr + 1)))	{
		for (j = 0; j < 4; j++)	{
			temp1[j] = RoundKey[(i - 1) * 4 + j];
		}
		if (i % Nk == 0) {
			{
				k = temp1[0];
				temp1[0] = temp1[1];
				temp1[1] = temp1[2];
				temp1[2] = temp1[3];
				temp1[3] = k;
			}
			{
				temp1[0] = getSBoxValue(temp1[0]);
				temp1[1] = getSBoxValue(temp1[1]);
				temp1[2] = getSBoxValue(temp1[2]);
				temp1[3] = getSBoxValue(temp1[3]);
			}

			temp1[0] = temp1[0] ^ Rcon[i / Nk];

		} else if (Nk > 6 && i % Nk == 4) {
			{
				temp1[0] = getSBoxValue(temp1[0]);
				temp1[1] = getSBoxValue(temp1[1]);
				temp1[2] = getSBoxValue(temp1[2]);
				temp1[3] = getSBoxValue(temp1[3]);
			}
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp1[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp1[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp1[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp1[3];
		i++;
	}
}

void AES_Decrypt::AddRoundKey(int round) {
	int i = 0;
	int j = 0;
	for (i = 0; i < 4; i++)	{
		for (j = 0; j < 4; j++)	{
			state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
}

void AES_Decrypt::InvSubBytes() {
	int i, j;
	for (i = 0; i < 4; i++)	{
		for (j = 0; j < 4; j++)	{
			state[i][j] = getSBoxInvert(state[i][j]);
		}
	}
}

void AES_Decrypt::InvShiftRows() {
	unsigned char temp = 0;

	temp = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	temp = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;
}

void AES_Decrypt::InvMixColumns() {
	int i = 0;
	unsigned char a, b, c, d;
	for (i = 0; i < 4; i++)	{

		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];
		
		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
}

void AES_Decrypt::InvCipher() {
	int i = 0;
	int j = 0;
	int round = 0;
	for (i = 0; i < 4; i++)	{
		for (j = 0; j < 4; j++)	{
			state[j][i] = in[i * 4 + j];
		}
	}
	AddRoundKey(Nr);

	for (round = Nr - 1; round > 0; round--) {
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			out[i * 4 + j] = state[j][i];
		}
	}
}

