#pragma once
#include "Sbox.h"
#include<string>
class Key {
public:
	int key[11][4]; //key[round][4*word]
	Key(Sbox*,std::string in);
	void makeKeyExpansion();//key 확장 함수
	int gFunction(int arr,int round); //g함수
	static void Word2Byte(char *des, int src); //word를 byte 배열로 바꿔준다
	static void Byte2Word(int *des, char *src);//byte 배열을 하나의 word로 바꿔줌
	~Key(); //소멸자
private:
	char keyMatrix[4][4];//처음 key값, key 블럭
	Sbox* mySbox;//sbox 객체
};