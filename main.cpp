#include <iostream>
#include <fstream>
#include <stdint.h>
using namespace std;

//uint32_t key[] = { 0xFDA5D54E,0xFC00B55A}; // encryption key
//uint32_t key[] = { 0x11223344, 0x55667788, 0x88AABBCC, 0xDDEEFF00 };
uint32_t key[] = { 0x00000000, 0x0000000, 0x00000000, 0x00000000 };
#define BLOCK_SIZE 8
uint32_t enc0;
uint32_t enc1;
uint32_t dec0;
uint32_t dec1;
uint32_t input1 = 0x2a72a594;
uint32_t input2 = 0x1072425f;



void xtea_encipher(unsigned int num_rounds, uint32_t const key[4]) {
	unsigned int i;
	//uint32_t v0 = v[0], v1 = v[1];
	uint32_t v0, v1, sum = 0, delta = 0x9E3779B9;
	//v0 = 0x04030201;
	//v1 = 0x08070605;
	v0 = input1;
	v1 = input2;

	cout << "v0 :";
	printf("%08x ", v0);
	cout << "\tv1 is :";
	printf("%08x ", v1);
	for (int i = 0; i < 4; i++)
	{
		printf("\nKey [%d] is :", i);
		printf("%08x ", key[i]);

	}
	for (i = 0; i < num_rounds; i++) {
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
		sum += delta;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
	}
	//v[0] = v0; v[1] = v1;
	enc0 = v0;
	enc1 = v1;
}

void xtea_decipher(unsigned int num_rounds, uint32_t enc0, uint32_t enc1, uint32_t const key[4]) {
	unsigned int i;
	//uint32_t v0 = v[0], v1 = v[1];
	uint32_t v0, v1, delta = 0x9E3779B9, sum = delta * num_rounds;
	v0 = input1;
	v1 = input2;

	for (i = 0; i < num_rounds; i++) {
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
	}
	//v[0] = v0; v[1] = v1;
	dec0 = v0;
	dec1 = v1;
}

int main()
{

	//FileCrypt("file.txt", true); // encrypt
	//if (encrypt)
	//	xtea_encipher(16, (uint32_t*)data, key);
	//else
	//	xtea_decipher(16, (uint32_t*)data, key);
	bool EncDec = true;


		xtea_encipher(16, key);


		cout << "\nEncrypted data: ";
		printf("%08x ", enc0);
		printf("\t%08x ", enc1);
		//FileCrypt("file.txt", false); // decrypt

		cout << "\n\nDecrypted data: ";
		xtea_decipher(16, enc0, enc1, key);
		printf("%08x ", dec0);
		printf("\t%08x ", dec1);
		cout << "Done";
	return 0;
}
