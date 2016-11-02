#define _CRT_SECURE_NO_WARNINGS
#include"Mode.h" //aes를 통해 mode를 이용하는 객체
#include<cstdio>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
string arr[] = { "ecb", "cbc","cfb","ofb","ctr" }; //모드 셋팅
int main(int argc, char *argv[]) {
	string plainT;
	char temp;
	if (argv[1][0]=='e') { //암호화
		cout << "enc..." << endl;
		for (int i = 0; i < 5; i++) {
			string tempString = arr[i];
			tempString += "_p.bin"; //모드에 해당하는 파일을 읽어드린다
			string cript;
			FILE *eOpen = fopen(tempString.c_str(), "rb");
			while (!feof(eOpen)) { temp = fgetc(eOpen); cript.push_back(temp); }
			Mode myMode(cript, "", ""); //mode 객체에서 암호화를 진행한다

			string outFile = arr[i] + "_c.bin";
			ofstream temp2(outFile.c_str(), ios::binary);
			temp2 << myMode.getResult(arr[i]);//결과 출력
			temp2.close();
		}
		cout << "done..." << endl;
	}
	else {
		cout << "dec..." << endl;
		for (int i = 0; i < 5; i++) {//복호화
			string tempString = arr[i];
			tempString += "_c.bin";
			string decript;
			FILE *eOpen = fopen(tempString.c_str(), "rb"); //cipher를 읽어들인다
			while (!feof(eOpen)) { temp = fgetc(eOpen); decript.push_back(temp); }
			Mode deMode(decript, "", "");//mode객체에서 복호화를 한다

			string outFile = arr[i] + "_p.bin";
			ofstream temp2(outFile.c_str(), ios::binary);
			temp2 << deMode.getDResult(arr[i]); //결과 출력
			temp2.close();
		}
		cout << "done..." << endl;
	}
}