#include"Key.h"
#include "GF8.h"
#include<cstring>
Key::Key(Sbox * s,std::string in) {
	mySbox = s;
	char keyB[] = "56e47a38c5598974bc46903dba290349";
	int temp = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { //keyB를 key matrix 4*4로 만들어 주는 과정
			char tempC = 0;
			if ('0' <= keyB[temp] && keyB[temp] <= '9') tempC += (keyB[temp] - '0') ;
			else if('a' <= keyB[temp] && keyB[temp] <= 'f') tempC+=(keyB[temp] - 'a') +10;
			tempC *= 16;
			if ('0' <= keyB[temp+1] && keyB[temp+1] <= '9') tempC += (keyB[temp+1] - '0') ;
			else if ('a' <= keyB[temp+1] && keyB[temp+1] <= 'f') tempC += (keyB[temp+1] - 'a') + 10;
			keyMatrix[j][i] = tempC;
			temp += 2;
		}
	}
	for (int i = 0; i < 4; i++) {
		char tempRow[4];
		for (int j = 0; j < 4; j++) tempRow[j] = keyMatrix[j][i]; 
		Key::Byte2Word(&key[0][i], tempRow);//첫번째 key 값을 셋팅한다
	}
}

void Key::makeKeyExpansion() {
	for (int j = 1; j < 11; j++) {
		key[j][0] = key[j - 1][0] ^ gFunction(key[j - 1][3],j); //gFunction을 통해 key를 셋팅
		for (int i = 1; i < 4; i++) {
			key[j][i] = key[j - 1][i] ^ key[j][i - 1];
		}
	}
}

int Key::gFunction(int arr,int round) {
	char tempRow[4];
	Key::Word2Byte(tempRow, arr);
	int temp = tempRow[0];

	for (int i = 0; i < 3; i++) { //shift 과정
		tempRow[i] = tempRow[i + 1];
	}
	tempRow[3] = temp;

	for (int i = 0; i < 4; i++) {
		tempRow[i] = mySbox->getSubstitute(tempRow[i]); //역원
	}

	for (int i = 1; i < 4; i++) tempRow[i] ^= 0;
	char rc = 1;
	rc = GF8::multiply(1, 1 << (round-1)); //roundkey를 더해준다
	tempRow[0] ^= rc;

	int res;
	Key::Byte2Word(&res, tempRow);
	return res;
}
void Key::Word2Byte(char *des, int src) {
	for (int i = 3; i >= 0; i--) {
		des[i] = 255;
		des[i] &= src;
		src >>= 8;
	}
}
void Key::Byte2Word(int* des, char *src) {
	(*des) = 0;
	for (int i = 0; i < 4; i++) {
		int temp = 255;
		temp &= src[i];
		(*des) |= temp;
		if (i == 3) break;
		else 
			(*des) <<= 8;
	}
}
Key::~Key() {
}