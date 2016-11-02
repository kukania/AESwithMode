#pragma once
#include "Sbox.h"
#include "Key.h"
#include<string>
using namespace std;
class AES {
public:
	AES(string in,string key);
	AES(char matrix[4][4], string key);
	/*암호화 중간 과정 함수*/
	void doingSbox(); 
	void doingShiftRow();
	void doingMixColumn();
	void doingAddkey(int); //암복호화에서 공통적으로 사용, param - round
	
	/*복호화 중간 과정 함수*/
	void doingDSbox();
	void doingDShiftRow();
	void doingDMixColumn();

	void doingAES(); //aes를 작동
	void doingDecrypt();//aes 복호화 작동
	string getCipher();//for debug - show hexa
	char plainMatrix[4][4];//블럭, 시작 값과 결과 값이 들어간다.
	void copyMatrix(char des[4][4], char arr[4][4]); //블럭 복사 ,arr을 des로 복사
	~AES();//소멸자
private:
	Sbox sbox; //sbox 객체
	void showMatrix(bool num);//for debug
	char changingMatrix[4][4];//중간 연산에서 필요하는 temp matrix
	Key *k; //key 객체
};