#define _CRT_SECURE_NO_WARNINGS
#include"Mode.h" //aes�� ���� mode�� �̿��ϴ� ��ü
#include<cstdio>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
string arr[] = { "ecb", "cbc","cfb","ofb","ctr" }; //��� ����
int main(int argc, char *argv[]) {
	string plainT;
	char temp;
	if (argv[1][0]=='e') { //��ȣȭ
		cout << "enc..." << endl;
		for (int i = 0; i < 5; i++) {
			string tempString = arr[i];
			tempString += "_p.bin"; //��忡 �ش��ϴ� ������ �о�帰��
			string cript;
			FILE *eOpen = fopen(tempString.c_str(), "rb");
			while (!feof(eOpen)) { temp = fgetc(eOpen); cript.push_back(temp); }
			Mode myMode(cript, "", ""); //mode ��ü���� ��ȣȭ�� �����Ѵ�

			string outFile = arr[i] + "_c.bin";
			ofstream temp2(outFile.c_str(), ios::binary);
			temp2 << myMode.getResult(arr[i]);//��� ���
			temp2.close();
		}
		cout << "done..." << endl;
	}
	else {
		cout << "dec..." << endl;
		for (int i = 0; i < 5; i++) {//��ȣȭ
			string tempString = arr[i];
			tempString += "_c.bin";
			string decript;
			FILE *eOpen = fopen(tempString.c_str(), "rb"); //cipher�� �о���δ�
			while (!feof(eOpen)) { temp = fgetc(eOpen); decript.push_back(temp); }
			Mode deMode(decript, "", "");//mode��ü���� ��ȣȭ�� �Ѵ�

			string outFile = arr[i] + "_p.bin";
			ofstream temp2(outFile.c_str(), ios::binary);
			temp2 << deMode.getDResult(arr[i]); //��� ���
			temp2.close();
		}
		cout << "done..." << endl;
	}
}