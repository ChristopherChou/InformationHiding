#pragma once
#include<math.h>
#include<iostream>
#define NUM 8
#define PI 3.1415926

//class DCT 
//���ֲο���https://blog.csdn.net/lwfcgz/article/details/8040550���������˽ϴ��޸�
class DCT
{
private:

public:
	int round(double a);//����������ֻ�ڷ��任ʱ���������
	void DiscreteCosineTransform(double input[NUM][NUM],double output[NUM][NUM]);//DCT���任
	void InverseDiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM]);//DCT���任
};

