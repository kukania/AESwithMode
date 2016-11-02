#include"Sbox.h"

int Sbox::getSubstitute(char input) {
	int temp = 255;
	temp &= input;
	temp=gf8.getInverse(temp);//������ ���� ����
	int tempRow[8] = { 0, }, cnt = 0;
	for (int i = 1; i < 256; i <<= 1) {
		tempRow[cnt++] = i&temp?1:0;
	}
	int resultRow[8];
	for (int i = 0; i < 8; i++) {
		resultRow[i] = 0;
		for (int j = 0; j < 8; j++) {
			resultRow[i] ^= tempRow[j] & matrix[i][j] ?1:0; //��İ����
		}
	}

	for (int i = 0; i < 8; i++) { resultRow[i] ^= addRow[i]; } //��� ���� ���
	int result = 0;
	temp = 1;
	for (int i = 0; i < 8; i++) {
		if (resultRow[i]) result |= temp;
		temp <<= 1;
	}

	return result;//��� ����
}

int Sbox::getInverse(char input) {
	int tempRow[8] = { 0, }, cnt = 0;
	for (int i = 1; i < 256; i <<= 1) {
		tempRow[cnt++] = i&input ? 1 : 0; //char -> bit�� �ٲ��ִ� ����
	}
	int resultRow[8];
	for (int i = 0; i < 8; i++) {
		resultRow[i] = 0;
		for (int j = 0; j < 8; j++) {
			resultRow[i] ^= tempRow[j] & inverseMatrix[i][j] ? 1 : 0; //��� ���
		}
	}

	for (int i = 0; i < 8; i++) { resultRow[i] ^= inverseRow[i]; } //��� �� ���
	int result = 0;
	int temp = 1;
	for (int i = 0; i < 8; i++) {
		if (resultRow[i]) result |= temp;
		temp <<= 1;
	}
	return gf8.getInverse(result); //���� ������
}