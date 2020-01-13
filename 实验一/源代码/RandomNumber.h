#pragma once


const int MAX_NUMBER = 10000;
const int RANDOMPRECISION = 10000;

class RandomNumber
{
protected:
	double uniformNumbers[MAX_NUMBER];//存放均匀分布随机数数组
	double expNumbers[MAX_NUMBER];//存放指数分布随机数数组
	double gaussNumbers[MAX_NUMBER];//存放高斯分布随机数数组
	double GGD05Numbers[MAX_NUMBER];//GGD,c=0.5
	double GGD10Numbers[MAX_NUMBER];//GGD,c=1.0
	double D, E;//高斯随机期望方差
public:
	RandomNumber();

	~RandomNumber();

	int Bernoulli();//返回01随机

	double uniform();//产生一个随机数
	int uniformDistribution();//产生均匀分布随机数

	int gaussDstribution();//产生高斯分布随机数
	int gaussExpectation();//估计高斯分布期望
	int gaussVar();//估计高斯分布方差

	int expDistribution(double beta,int out=1);//求指数分布随机数，out为可选项，为1默认输出到文件中
	int expBeta();//估计指数分布beta

	int GGD05(double beta);
	int GGD10(double beta);

};
