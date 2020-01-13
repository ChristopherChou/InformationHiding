#include "RandomNumber.h"
#include<random>
#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>

using namespace std;

RandomNumber::RandomNumber()
{

}

RandomNumber::~RandomNumber()
{

}

//随机产生0或1
int RandomNumber::Bernoulli()
{
	int a;
	random_device rd;
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(0, RANDOMPRECISION);
	a = dis(gen);
	a = a % 2;
	return a;
}

//产生一个随机数（0-1）
double RandomNumber::uniform()
{
	int a;
	double f;
	random_device rd;
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(0, RANDOMPRECISION);
	a = dis(gen);
	a = a % RANDOMPRECISION;
	f = (double)a;
	f = f / (double)RANDOMPRECISION;
	return f;
}

//(0,1)匀分布
int RandomNumber::uniformDistribution()
{
	for (int i = 0; i < MAX_NUMBER; i++)
		uniformNumbers[i] = uniform();

	ofstream outfile("uniform.txt", ios::out);
	for (int i = 0; i < MAX_NUMBER; i++)
		outfile << uniformNumbers[i] << endl;
	return 0;
}

int RandomNumber::gaussDstribution()
{
	const double PI = 3.1415926;
	int j;
	double A, B, C, data;
	double uni[2];
	D = uniform();	//产生一个随机方差
	E = uniform();	//产生一个随机期望
	for (j = 0; j < MAX_NUMBER; j++) {
		uni[0] = uniform();
		if (0 == uni[0])
			uni[0] += 0.001;
		uni[1] = uniform();
		A = sqrt((-2) * log(uni[0]));
		B = 2 * PI * uni[1];
		C = A * cos(B);
		data = E + C * D;
		gaussNumbers[j] = data;
	}
	ofstream outfile("gauss.txt", ios::out);
	for (int i = 0; i < MAX_NUMBER; i++)
		outfile << gaussNumbers[i] << endl;

	return 0;
}

int RandomNumber::gaussExpectation()
{
	double sum = 0;
	double mean;
	for (int i = 0; i < MAX_NUMBER; i++)
		sum += gaussNumbers[i];
	mean = sum / MAX_NUMBER;
	ofstream outfile("GaussExp.txt", ios::out);
	outfile << "随机产生的期望为：" << E << endl;
	outfile << "估计的期望为：" << mean << endl;
	return 0;
}

int RandomNumber::gaussVar()
{
	double sum = 0;
	double mean;
	for (int i = 0; i < MAX_NUMBER; i++)
		sum += gaussNumbers[i];
	mean = sum / MAX_NUMBER;

	double v_sum = 0;
	double variance;
	for (int i = 0; i < MAX_NUMBER; i++)
		v_sum += (gaussNumbers[i] - mean) * (gaussNumbers[i] - mean);
	variance = v_sum / MAX_NUMBER;
	ofstream outfile("GaussVar.txt", ios::out);
	outfile << "随机产生的方差为：" <<D << endl;
	outfile << "估计的方差为：" << variance << endl;
	return 0;
}

//指数分布
int RandomNumber::expDistribution(double beta,int out)
{
	
	for (int i = 0; i < MAX_NUMBER; i++)
		expNumbers[i] = -beta * log(1.0 - uniformNumbers[i]);

	if (out)
	{
		ofstream outfile("exp.txt", ios::out);
		for (int i = 0; i < MAX_NUMBER; i++)
			outfile << expNumbers[i] << endl;
	}
	return 0;
}

//求指数分布的beta
int RandomNumber::expBeta()
{
	//指数分布的期望就是beta
	double average = 0;
	for (int i = 0; i < MAX_NUMBER; i++)
		average += expNumbers[i];
	average /= (double)MAX_NUMBER;

	//输出到文件
	ofstream outfile("expBeta.txt", ios::out);
	outfile <<"Beta的估计值为"<< average << endl;
//	cout << average << endl;
	return 0;
}

int RandomNumber::GGD05(double beta)
{
	double * GGDtemp1= new double[MAX_NUMBER];
	double* GGDtemp2 = new double[MAX_NUMBER];

	//第一个指数分布
	expDistribution(beta, 0);
	for (int i = 0; i < MAX_NUMBER; i++)
		GGDtemp1[i] = expNumbers[i];

	//第二个指数分布
	expDistribution(beta, 0);
	for (int i = 0; i < MAX_NUMBER; i++)
		GGDtemp2[i] = expNumbers[i];

	//排序后相加
	sort(GGDtemp1, GGDtemp1+MAX_NUMBER);
	sort(GGDtemp2, GGDtemp2+MAX_NUMBER);
	for (int i = 0; i < MAX_NUMBER; i++)
		GGDtemp1[i] += GGDtemp2[i];


	for (int i = 0; i < MAX_NUMBER; i++)
	{
		if (Bernoulli())
			GGD05Numbers[i] = GGDtemp1[i]* GGDtemp1[i];
		else
			GGD05Numbers[i] = -GGDtemp1[i]* GGDtemp1[i];
	}

	ofstream outfile("GGD05.txt", ios::out);
	for (int i = 0; i < MAX_NUMBER; i++)
		outfile << GGD05Numbers[i]<<endl;

	delete [] GGDtemp1;
	delete[] GGDtemp2;
	return 0;
}

int RandomNumber::GGD10(double beta)
{
	expDistribution(beta, 0);
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		if (Bernoulli())
			GGD10Numbers[i] = expNumbers[i];
		else
			GGD10Numbers[i] = -expNumbers[i];
	}

	ofstream outfile("GGD10.txt", ios::out);
	for (int i = 0; i < MAX_NUMBER; i++)
		outfile << GGD10Numbers[i] << endl;

	return 0;
}

