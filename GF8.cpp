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
int GF8::getInverse(int input) { //역원을 구한다
	if (input == 1) return 1;
	else {
		if (input == 0) return 0;
		uclide(input,bit); //일단 유클리드 함수를 실행해
		return extendUclide(input); //확장 유클리드 함수를 통해 역원을 리턴
	}
}
void GF8::uclide(int input,int bit) {
	int tempInput=input;
	int tempBit = bit;
	int inputMbit=getMaxBit(input), bitMbit= getMaxBit(bit);
	int temp=0;
	while (inputMbit <= bitMbit) { //두 수의 계수를 비교해서 나눠준다
		int temp2 = bitMbit - inputMbit;
		tempInput <<= temp2;
		bit = (input << temp2) ^ bit;
		temp |=(1<<temp2);
		inputMbit = getMaxBit(input);
		bitMbit = getMaxBit(bit);
	};

	uclideQ.push_back(temp); //유클리드 계산에서 나눗셈 결과를 입력
	if (bit == 1)return;
	else {
		bit > input ? uclide(input, bit) : uclide(bit, input);
	}
}
int GF8::extendUclide(int input) { //확장 유클리드 계산 과정
	int a=1, ap=0; //a는 현재 몫, ap는 전의 몫
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
int GF8::getMaxBit(int input) { //입력 받음 값의 최대 비트 자리를 리턴함
	int temp = 256;
	int len = 9;
	while (input / temp == 0) {
		temp /=2;
		len--;
	}
	return len;
}
int GF8::multiply(int a, int b) { //GF의 곱셈연산
	int res = 0;
	for (int i = 0; i < 8; i++) { //일단은 다 곱하고
		if (a&(1 << i)) {
			res ^= b << i;
		} 
	}
	for (int i = 16; i >= 8; i--) { //X^8이하의 차수로 낮춰 준다
		if (res&(1 << i)) {
			res ^= 0x11b << (i - 8);
		}
	}
	return res;
}