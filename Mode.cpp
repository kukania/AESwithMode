#include"Mode.h"
Mode::Mode(string plain, string key, string lv) {
	this->plain = plain;
	this->key = key;
	this->lv = lv;
	int temp = 0;
	char tempLv[] = "8ce82eefbea0da3c44699ed7db51b7d9";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { //iv 값을 ivM으로 만들어주는 과정
			char tempC = 0;
			if ('0' <= tempLv[temp] && tempLv[temp] <= '9') tempC += (tempLv[temp] - '0');
			else if ('a' <= tempLv[temp] && tempLv[temp] <= 'f') tempC += (tempLv[temp] - 'a') + 10;
			tempC *= 16;
			if ('0' <= tempLv[temp + 1] && tempLv[temp + 1] <= '9') tempC += (tempLv[temp + 1] - '0');
			else if ('a' <= tempLv[temp + 1] && tempLv[temp + 1] <= 'f') tempC += (tempLv[temp + 1] - 'a') + 10;

			lvM[j][i] = tempC;
			temp += 2;
		}
	}
}
string Mode::getResult(string mode) { //mode에 따라 수행한다
	if (mode.compare("ecb") == 0) {
		start = 0;
		ecb();
		return this->result;
	}
	else if (mode.compare("cbc") == 0) {
		start = 0;
		cbc();
		return this->result;
	}
	else if (mode.compare("cfb") == 0) {
		start = 0;
		cfb();
		return this->result;
	}
	else if (mode.compare("ofb") == 0) {
		start = 0;
		ofb();
		return this->result;
	}
	else if (mode.compare("ctr") == 0) {
		start = 0;
		ctr();
		return this->result;
	}
}
void Mode::ecb() {
	result.clear();
	do {
		string tempPlain = makeNextPlain(); //블럭을 읽어옴
		if (tempPlain.compare("") == 0) break;
		this->aes = new AES(tempPlain, key);
		this->aes->doingAES(); //단순히 AES를 한다
		this->aes->copyMatrix(this->pResult, aes->plainMatrix);
		this->makeResultString();
		delete aes;
	} while (1);
}
void Mode::cbc() {
	result.clear();
	string tempPlain;
	char tempMatrix[4][4];
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) { //블럭을 읽어옴
		int t = 0;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) { //다음에 넘겨줄 cipher를 저장할 공간
				tempMatrix[k][j] = tempPlain[t++];
			}
		}
		if (i == 0) {
			this->matrixXOR(tempMatrix, this->lvM);
		}
		else {
			this->matrixXOR(tempMatrix, this->pResult);
		}
		this->aes = new AES(tempMatrix, key); //xor 한 값을 통해 aes구현
		this->aes->doingAES();
		this->aes->copyMatrix(pResult, aes->plainMatrix);
		this->makeResultString();
		delete aes;
	}

}
void Mode::cfb() {
	result.clear();

	string tempPlain;
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) { //블럭을 읽어옴
		if (i == 0) {
			this->aes = new AES(lvM, key);
		}
		else
			this->aes = new AES(pResult, key);
		makeStringToMatrix(tempPlain);
		this->aes->doingAES();
		this->matrixXOR(pResult, aes->plainMatrix);
		this->makeResultString(); 
		delete aes;
	}
}
void Mode::ofb() {
	result.clear();

	string tempPlain;
	AES * temp = NULL;
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) {
		makeStringToMatrix(tempPlain);
		if (i == 0)
			this->aes = new AES(lvM, key);
		else
			this->aes = temp;
		this->aes->doingAES();
		temp = new AES(this->aes->plainMatrix, key);

		this->matrixXOR(pResult, aes->plainMatrix);
		this->makeResultString();

		delete aes;
	}
	delete temp;
}
void Mode::ctr() {
	result.clear();
	string tempPlain;
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) {
		this->aes = new AES(lvM, key);
		this->aes->doingAES();
		makeStringToMatrix(tempPlain);

		this->matrixXOR(pResult, aes->plainMatrix);
		this->makeResultString();

		makeCheckIVOver();//add iv;
		delete aes;
	}
}
void Mode::matrixXOR(char arr[4][4], char arr2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arr[i][j] ^= arr2[i][j];
		}
	}
}
string Mode::makeNextPlain() {
	if (start >= plain.size() - 1) return "";
	string res = plain.substr(start, 16);
	start += 16;
	return res;
}
void Mode::makeResultString() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { //중간 결과를 합한 전체 결과를 만들어 준다
			result.push_back(pResult[j][i]);
		}
	}
}
void Mode::makeStringToMatrix(string in) {
	int temp = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult[j][i] = in[temp++];
		}
	}
}
string Mode::getDResult(string mode) {
	if (mode.compare("ecb") == 0) {
		start = 0;
		Decb();
		return this->result;
	}
	else if (mode.compare("cbc") == 0) {
		start = 0;
		Dcbc();
		return this->result;
	}
	else if (mode.compare("cfb") == 0) {
		start = 0;
		Dcfb();
		return this->result;
	}
	else if (mode.compare("ofb") == 0) {
		start = 0;
		Dofb();
		return this->result;
	}
	else if (mode.compare("ctr") == 0) {
		start = 0;
		Dctr();
		return this->result;
	}
}
void Mode::makeCheckIVOver() {
	for (int i = 3; i >= 0; i--) {
		for (int j = 3; j >= 0; j--) {
			if (int temp=(lvM[j][i] + 1) > 0xff) { //현재 자리의 비트에서 1을 더했을때 over일 경우
				lvM[j][i] = 0;
			}
			else {
				lvM[j][i] += 1; //아닐경우 1을 더하고 return;
				return;
			}
		}
	}
}
void Mode::Decb() {
	result.clear();
	do {
		string tempPlain = makeNextPlain();
		if (tempPlain.compare("") == 0) break;
		this->aes = new AES(tempPlain, key);//글자 단위로 끊어야됨
		this->aes->doingDecrypt(); //AES decrypt;
		this->aes->copyMatrix(this->pResult, aes->plainMatrix);
		this->makeResultString();
		delete aes;
	} while (1);
}
void Mode::Dcbc() {
	result.clear();
	string tempPlain;
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) {
		this->aes = new AES(tempPlain, key);
		this->aes->doingDecrypt();
		if (i == 0) {
			this->matrixXOR(aes->plainMatrix, this->lvM);
		}
		else {
			this->matrixXOR(aes->plainMatrix, this->pResult);
		}
		this->aes->copyMatrix(pResult, aes->plainMatrix);
		this->makeResultString();
		makeStringToMatrix(tempPlain);
		delete aes;
	}
}
void Mode::Dcfb() {
	result.clear();
	string tempPlain;
	for (int i = 0; (tempPlain = makeNextPlain()).compare("") != 0; i++) {
		if (i == 0) {
			this->aes = new AES(lvM, key);
		}
		else
			this->aes = new AES(pResult, key);
		this->aes->doingAES();
		makeStringToMatrix(tempPlain);
		this->matrixXOR(pResult, aes->plainMatrix);
		this->makeResultString();
		makeStringToMatrix(tempPlain);
		delete aes;
	}
}
void Mode::Dofb() {
	ofb(); //decryption과 encryption 과정 동일
}
void Mode::Dctr() {
	ctr();//decryption과 encryption 과정 동일
}