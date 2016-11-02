#include "GF8.h"
int GF8::x8 = 27;
GF8::GF8() {
	bit = 0;
	int arr[] = { 1,1,0,1,1,0,0,0,1 };
	for (int i = 8; i >= 0; i--) {
		if (arr[i]) {
			bit |= 1;
		}
		if (i == 0) break;
		bit <<= 1;
	}
}
int GF8::getInverse(int input) { //������ ���Ѵ�
	if (input == 1) return 1;
	else {
		if (input == 0) return 0;
		uclide(input,bit); //�ϴ� ��Ŭ���� �Լ��� ������
		return extendUclide(input); //Ȯ�� ��Ŭ���� �Լ��� ���� ������ ����
	}
}
void GF8::uclide(int input,int bit) {
	int tempInput=input;
	int tempBit = bit;
	int inputMbit=getMaxBit(input), bitMbit= getMaxBit(bit);
	int temp=0;
	while (inputMbit <= bitMbit) { //�� ���� ����� ���ؼ� �����ش�
		int temp2 = bitMbit - inputMbit;
		tempInput <<= temp2;
		bit = (input << temp2) ^ bit;
		temp |=(1<<temp2);
		inputMbit = getMaxBit(input);
		bitMbit = getMaxBit(bit);
	};

	uclideQ.push_back(temp); //��Ŭ���� ��꿡�� ������ ����� �Է�
	if (bit == 1)return;
	else {
		bit > input ? uclide(input, bit) : uclide(bit, input);
	}
}
int GF8::extendUclide(int input) { //Ȯ�� ��Ŭ���� ��� ����
	int a=1, ap=0; //a�� ���� ��, ap�� ���� ��
	for (int i = 0; i < uclideQ.size(); i++) {
		int temp = a;
		
		int result=0;
		int cnt = 256,len=8;
		while (cnt != 0) {
			if (uclideQ[i] & cnt) {
				result ^= a << len;
			}
			len--;
			cnt /=2;
		}
		a = ap^result;
		ap = temp;
	}
	uclideQ.clear();
	return a;
}
int GF8::getMaxBit(int input) { //�Է� ���� ���� �ִ� ��Ʈ �ڸ��� ������
	int temp = 256;
	int len = 9;
	while (input / temp == 0) {
		temp /=2;
		len--;
	}
	return len;
}
int GF8::multiply(int a, int b) { //GF�� ��������
	int res = 0;
	for (int i = 0; i < 8; i++) { //�ϴ��� �� ���ϰ�
		if (a&(1 << i)) {
			res ^= b << i;
		} 
	}
	for (int i = 16; i >= 8; i--) { //X^8������ ������ ���� �ش�
		if (res&(1 << i)) {
			res ^= 0x11b << (i - 8);
		}
	}
	return res;
}