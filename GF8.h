#pragma once
#include<vector>
class GF8 {
// x^8 + x^4 + x^3 + x + 1
public:
	GF8();
	int getInverse(int input); //역원을 가지고 온다
	static int x8; //x^8일때의 mod 값
	static int multiply(int a, int b);//gf(2^8)안에서의 곱셈을 계산
private:
	void uclide(int,int); //유클리드 함수 구현
	int extendUclide(int);//확장 유클리드 함수 구현
	int getMaxBit(int);//각 값의 가장 최상위 비트 값을 리턴
	int bit;
	std::vector<int>uclideQ;//유클리드 계산 결과를 저장
};