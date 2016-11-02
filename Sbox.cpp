#include"Sbox.h"

int Sbox::getSubstitute(char input) {
	int temp = 255;
	temp &= input;
	temp=gf8.getInverse(temp);//역원을 가져 오고
	int tempRow[8] = { 0, }, cnt = 0;
	for (int i = 1; i < 256; i <<= 1) {
		tempRow[cnt++] = i&temp?1:0;
	}
	int resultRow[8];
	for (int i = 0; i < 8; i++) {
		resultRow[i] = 0;
		for (int j = 0; j < 8; j++) {
			resultRow[i] ^= tempRow[j] & matrix[i][j] ?1:0; //행렬곱계산
		}
	}

	for (int i = 0; i < 8; i++) { resultRow[i] ^= addRow[i]; } //행렬 덧셈 계산
	int result = 0;
	temp = 1;
	for (int i = 0; i < 8; i++) {
		if (resultRow[i]) result |= temp;
		temp <<= 1;
	}

	return result;//결과 리턴
}

int Sbox::getInverse(char input) {
	int tempRow[8] = { 0, }, cnt = 0;
	for (int i = 1; i < 256; i <<= 1) {
		tempRow[cnt++] = i&input ? 1 : 0; //char -> bit로 바꿔주는 과정
	}
	int resultRow[8];
	for (int i = 0; i < 8; i++) {
		resultRow[i] = 0;
		for (int j = 0; j < 8; j++) {
			resultRow[i] ^= tempRow[j] & inverseMatrix[i][j] ? 1 : 0; //행렬 계산
		}
	}

	for (int i = 0; i < 8; i++) { resultRow[i] ^= inverseRow[i]; } //행렬 곱 계산
	int result = 0;
	int temp = 1;
	for (int i = 0; i < 8; i++) {
		if (resultRow[i]) result |= temp;
		temp <<= 1;
	}
	return gf8.getInverse(result); //역원 가져옴
}