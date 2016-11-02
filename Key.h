#pragma once
#include "Sbox.h"
#include<string>
class Key {
public:
	int key[11][4]; //key[round][4*word]
	Key(Sbox*,std::string in);
	void makeKeyExpansion();//key Ȯ�� �Լ�
	int gFunction(int arr,int round); //g�Լ�
	static void Word2Byte(char *des, int src); //word�� byte �迭�� �ٲ��ش�
	static void Byte2Word(int *des, char *src);//byte �迭�� �ϳ��� word�� �ٲ���
	~Key(); //�Ҹ���
private:
	char keyMatrix[4][4];//ó�� key��, key ��
	Sbox* mySbox;//sbox ��ü
};