#include"AES.h" //aes ��ȣȭ�� �ϴ� �ش�
class Mode {
public:
	Mode(string plain, string key, string lv);
	string getResult(string mode); //��ȣȭ ����� mode ���� �����ؼ� ������ �� �ִ�
	string getDResult(string mode);//��ȣȭ ����� mode ���� �����ؼ� ������ �� �մ�.

	/*��ȣȭ mode*/
	void ecb();
	void cbc();
	void cfb();
	void ofb();
	void ctr();
	/*��ȣȭ mode*/
	void Decb();
	void Dcbc();
	void Dcfb();
	void Dofb();
	void Dctr();
private:
	void matrixXOR(char arr[4][4], char arr2[4][4]); //matrix���� xor ������ �Ͽ� arr�� �����Ѵ�
	string makeNextPlain();//��,�Ǵ� ��ȣ���� �� ������ �о�´�
	void makeStringToMatrix(string input);//string���� �Ѿ���� ���� 4*4��ķ� �����(����� pResult)
	void makeResultString();//��(��)ȣȭ-pResult- ����� string���� �ٲپ� �ش�
	void makeCheckIVOver();//Iv���� ���� ��������, �ڸ��ø��� ó���ϱ� ���� �Լ�
	char lvM[4][4]; //iv��
	char pResult[4][4];//�� ����� ����� �Ǵ� �о� ���� �� ��
	int start; //makeNextPlain�� �ϱ� ���� int�� ����
	
	/*������°͵�*/
	string key;
	string plain; 
	string lv;

	string result; //���� ���
	AES * aes;//aes�� �ϴ� ��ü
};