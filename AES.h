#pragma once
#include "Sbox.h"
#include "Key.h"
#include<string>
using namespace std;
class AES {
public:
	AES(string in,string key);
	AES(char matrix[4][4], string key);
	/*��ȣȭ �߰� ���� �Լ�*/
	void doingSbox(); 
	void doingShiftRow();
	void doingMixColumn();
	void doingAddkey(int); //�Ϻ�ȣȭ���� ���������� ���, param - round
	
	/*��ȣȭ �߰� ���� �Լ�*/
	void doingDSbox();
	void doingDShiftRow();
	void doingDMixColumn();

	void doingAES(); //aes�� �۵�
	void doingDecrypt();//aes ��ȣȭ �۵�
	string getCipher();//for debug - show hexa
	char plainMatrix[4][4];//��, ���� ���� ��� ���� ����.
	void copyMatrix(char des[4][4], char arr[4][4]); //�� ���� ,arr�� des�� ����
	~AES();//�Ҹ���
private:
	Sbox sbox; //sbox ��ü
	void showMatrix(bool num);//for debug
	char changingMatrix[4][4];//�߰� ���꿡�� �ʿ��ϴ� temp matrix
	Key *k; //key ��ü
};