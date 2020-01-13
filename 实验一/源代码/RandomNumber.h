#pragma once


const int MAX_NUMBER = 10000;
const int RANDOMPRECISION = 10000;

class RandomNumber
{
protected:
	double uniformNumbers[MAX_NUMBER];//��ž��ȷֲ����������
	double expNumbers[MAX_NUMBER];//���ָ���ֲ����������
	double gaussNumbers[MAX_NUMBER];//��Ÿ�˹�ֲ����������
	double GGD05Numbers[MAX_NUMBER];//GGD,c=0.5
	double GGD10Numbers[MAX_NUMBER];//GGD,c=1.0
	double D, E;//��˹�����������
public:
	RandomNumber();

	~RandomNumber();

	int Bernoulli();//����01���

	double uniform();//����һ�������
	int uniformDistribution();//�������ȷֲ������

	int gaussDstribution();//������˹�ֲ������
	int gaussExpectation();//���Ƹ�˹�ֲ�����
	int gaussVar();//���Ƹ�˹�ֲ�����

	int expDistribution(double beta,int out=1);//��ָ���ֲ��������outΪ��ѡ�Ϊ1Ĭ��������ļ���
	int expBeta();//����ָ���ֲ�beta

	int GGD05(double beta);
	int GGD10(double beta);

};
