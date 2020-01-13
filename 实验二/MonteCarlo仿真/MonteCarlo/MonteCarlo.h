#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <fstream>
#include<random>

//const double a = 1.8;//嵌入强度
const double PI = 3.14159;//
const int N = 1000;//每组1000个数据
using namespace std;

class MonteCarlo {
private:
	int* W;//水印序列
	//double* GGD05num;//随机数组
	//double* GGD10num;//随机数组
	//double* GGD20num;
	double* X;//随机序列
	double* S1;//嵌入后的数组
	double* S0;//不嵌入

public:
	MonteCarlo();
	~MonteCarlo();
	double ierfc(const double y);  //根据误检概率求Q的反函数以获得阈值
	int GGD05();//c=0.5的GGD分布
	int GGD10();//c=1.0的GGD分布
	int GGD20();//C=2.0的GGD分布=高斯分布
	int Gauss();//高斯分布
	int inset(double a=1.8);//嵌入水印
	int DetectPm(double test );//检测嵌入
	int DetectPfa(double test);//检测未嵌入
	double CaculateTest(const double x);  //阈值
	double CaculatePm(const double x,double a=1.8);  //由Pfa计算理论Pm
	int attack(double STD);//添加噪声2.5

};