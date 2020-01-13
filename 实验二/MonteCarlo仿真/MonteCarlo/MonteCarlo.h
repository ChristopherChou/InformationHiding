#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <fstream>
#include<random>

//const double a = 1.8;//Ƕ��ǿ��
const double PI = 3.14159;//
const int N = 1000;//ÿ��1000������
using namespace std;

class MonteCarlo {
private:
	int* W;//ˮӡ����
	//double* GGD05num;//�������
	//double* GGD10num;//�������
	//double* GGD20num;
	double* X;//�������
	double* S1;//Ƕ��������
	double* S0;//��Ƕ��

public:
	MonteCarlo();
	~MonteCarlo();
	double ierfc(const double y);  //������������Q�ķ������Ի����ֵ
	int GGD05();//c=0.5��GGD�ֲ�
	int GGD10();//c=1.0��GGD�ֲ�
	int GGD20();//C=2.0��GGD�ֲ�=��˹�ֲ�
	int Gauss();//��˹�ֲ�
	int inset(double a=1.8);//Ƕ��ˮӡ
	int DetectPm(double test );//���Ƕ��
	int DetectPfa(double test);//���δǶ��
	double CaculateTest(const double x);  //��ֵ
	double CaculatePm(const double x,double a=1.8);  //��Pfa��������Pm
	int attack(double STD);//�������2.5

};