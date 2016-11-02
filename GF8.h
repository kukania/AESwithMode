#pragma once
#include<vector>
class GF8 {
// x^8 + x^4 + x^3 + x + 1
public:
	GF8();
	int getInverse(int input); //������ ������ �´�
	static int x8; //x^8�϶��� mod ��
	static int multiply(int a, int b);//gf(2^8)�ȿ����� ������ ���
private:
	void uclide(int,int); //��Ŭ���� �Լ� ����
	int extendUclide(int);//Ȯ�� ��Ŭ���� �Լ� ����
	int getMaxBit(int);//�� ���� ���� �ֻ��� ��Ʈ ���� ����
	int bit;
	std::vector<int>uclideQ;//��Ŭ���� ��� ����� ����
};