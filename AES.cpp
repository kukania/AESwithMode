#define _CRT_SECURE_NO_WARNINGS
#include "AES.h"
#include"Key.h"
#include<iostream>
#include<cstring>
AES::AES(string in, string input) { //블럭을 string으로 받을때
	int temp = 0;
	memset(plainMatrix, 0, sizeof(plainMatrix));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plainMatrix[j][i] = in[temp++];
		}
	}
	k = new Key(&sbox, input);
	k->makeKeyExpansion();
}
AES::AES(char matrix[4][4], string key) { //블럭을 matrix로 받을때
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) plainMatrix[i][j] = matrix[i][j];
	}
	k = new Key(&sbox, key);
	k->makeKeyExpansion();
}
void AES::doingSbox() { //sbox 과정
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			changingMatrix[i][j] = sbox.getSubstitute(plainMatrix[i][j]);
		}
	}
}
void AES::doingShiftRow() {
	for (int i = 1; i < 4; i++) { //shift 과정
		int temp[4];
		for (int j = 0; j < 4; j++)temp[j] = changingMatrix[i][j];
		for (int j = 0; j < 4; j++) {
			changingMatrix[i][j % 4] = temp[(j + i) % 4];
		}
	}
}
void AES::doingMixColumn() {
	int matrix[4][4] = {
		{2,3,1,1},
		{1,2,3,1},
		{1,1,2,3},
		{3,1,1,2}
	};

	for (int i = 0; i < 4; i++) { //행렬곱 과정
		int tempColumn[4], tempMatrix[4];
		for (int j = 0; j < 4; j++)	tempColumn[j] = changingMatrix[j][i];
		for (int j = 0; j < 4; j++) {
			int result = 0;
			for (int k = 0; k < 4; k++) tempMatrix[k] = matrix[j][k];
			plainMatrix[j][i] = 0;
			for (int k = 0; k < 4; k++) {
				result ^= GF8::multiply(tempColumn[k], tempMatrix[k]);
			}
			plainMatrix[j][i] = result;
		}
	}
}

void AES::doingAddkey(int num) { //key 값을 더해준다
	for (int i = 0; i < 4; i++) {
		int result;
		char temp[4];
		for (int k = 0; k < 4; k++) temp[k] = plainMatrix[k][i];
		Key::Byte2Word(&result, temp);
		result ^= k->key[num][i];
		Key::Word2Byte(temp, result);
		for (int k = 0; k < 4; k++) plainMatrix[k][i]=temp[k];
	}
}

string AES::getCipher() { //for debug
	string result;
	char buf[3];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sprintf(buf, "%02x", plainMatrix[j][i]);
			result += buf;
		}
	}
	return result;
}

void AES::doingAES() { //총 aes를 수행
	doingAddkey(0);
	for (int i = 1; i <= 10; i++) {
		doingSbox();
		doingShiftRow();
		if (i != 10)
			doingMixColumn();
		else
			copyMatrix(plainMatrix,changingMatrix);
		doingAddkey(i);
	}
}

void AES::showMatrix(bool num) { //for debug
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (num) {
				std::cout <<std::hex<< plainMatrix[i][j] << " ";
			}
			else
				std::cout << std::hex << changingMatrix[i][j] << " ";
		}
		std::cout << endl;
	}
}
void AES::copyMatrix(char des[4][4],char arr[4][4]) { //matrix 복사
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			des[i][j] = arr[i][j];
		}
	}
}

void AES::doingDSbox() {//decrypt sbox
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plainMatrix[i][j] = sbox.getInverse(changingMatrix[i][j]);
		}
	}
}
void AES::doingDShiftRow() {//decrypt shif row
	for (int i = 1; i <4; i++) {
		int temp[4];
		for (int j = 0; j < 4; j++)temp[j] = changingMatrix[i][j];
		for (int j = 0; j < 4; j++) {
			changingMatrix[i][j % 4] = temp[(j + (4-i)) % 4];
		}
	}
}
void AES::doingDMixColumn() { //dcrypt mixcolumn
	int matrix[4][4] = {
		{ 14,11,13,9 },
		{ 9,14,11,13 },
		{ 13,9,14,11 },
		{ 11,13,9,14 }
	};

	for (int i = 0; i < 4; i++) {
		int tempColumn[4], tempMatrix[4];
		for (int j = 0; j < 4; j++)	tempColumn[j] = plainMatrix[j][i];
		for (int j = 0; j < 4; j++) {
			int result = 0;
			for (int k = 0; k < 4; k++) tempMatrix[k] = matrix[j][k];
			changingMatrix[j][i] = 0;
			for (int k = 0; k < 4; k++) {
				result ^= GF8::multiply(tempColumn[k], tempMatrix[k]);
			}
			changingMatrix[j][i] = result;
		}
	}
}
void AES::doingDecrypt() { //decrypt
	doingAddkey(10);
	for (int i = 10; i >= 1; i--) {
		if (i != 10)
			doingDMixColumn();
		else
			copyMatrix(changingMatrix,plainMatrix);
		doingDShiftRow();
		doingDSbox();
		doingAddkey(i - 1);
	}
}


AES::~AES() {
	delete k;
}