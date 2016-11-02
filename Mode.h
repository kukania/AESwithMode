#include"AES.h" //aes 암호화를 하는 해더
class Mode {
public:
	Mode(string plain, string key, string lv);
	string getResult(string mode); //암호화 결과를 mode 별로 선택해서 가져올 수 있다
	string getDResult(string mode);//복호화 결과를 mode 별로 선택해서 가져올 수 잇다.

	/*암호화 mode*/
	void ecb();
	void cbc();
	void cfb();
	void ofb();
	void ctr();
	/*복호화 mode*/
	void Decb();
	void Dcbc();
	void Dcfb();
	void Dofb();
	void Dctr();
private:
	void matrixXOR(char arr[4][4], char arr2[4][4]); //matrix간의 xor 연산을 하여 arr에 저장한다
	string makeNextPlain();//평문,또는 암호문을 블럭 단위로 읽어온다
	void makeStringToMatrix(string input);//string으로 넘어오는 블럭을 4*4행렬로 만든다(결과는 pResult)
	void makeResultString();//암(복)호화-pResult- 결과를 string으로 바꾸어 준다
	void makeCheckIVOver();//Iv값을 증가 시켰을때, 자리올림을 처리하기 위한 함수
	char lvM[4][4]; //iv값
	char pResult[4][4];//한 블록의 결과값 또는 읽어 오는 블럭 값
	int start; //makeNextPlain을 하기 위한 int형 변수
	
	/*쓸모없는것들*/
	string key;
	string plain; 
	string lv;

	string result; //최종 결과
	AES * aes;//aes를 하는 객체
};