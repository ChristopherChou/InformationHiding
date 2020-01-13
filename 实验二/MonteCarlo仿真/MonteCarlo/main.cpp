#include <iostream>
#include <string>
#include"MonteCarlo.h"
#include<fstream>

int main()
{
	const int M = 6;
	ofstream out("result.txt", ios::out);
	MonteCarlo* test;


	double ThyPfa[M] , ExpPfa[M] ;
	double ThyPm[M] , ExpPm[M] ;
	double Phi[M];
	//理论Pfa
	ThyPfa[0] = 1e-6;
	for (int i = 0; i < M-1; i++)
		ThyPfa[i + 1] = ThyPfa[i] *10 ;
	out << "无攻击理论误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ThyPfa[i] << " ";
	out << endl;
	//计算阈值
	test = new MonteCarlo;
	out << "检测阈值为" << endl;
	for (int i = 0; i < M; i++)
	{
		Phi[i] = test->CaculateTest(ThyPfa[i]);
		out << Phi[i] << " ";
	}
	out << endl;
	//计算理论漏检概率
	out << "无攻击理论漏检概率为" << endl;
	for (int i = 0; i < M; i++)
	{
		ThyPm[i] = test->CaculatePm(ThyPfa[i]);
		out << ThyPm[i] << " ";
	}
	out << endl;

	delete test;
	int countPm = 0;
	int countPfa = 0;


	//无攻击情况
	//c=2.0
	//a=1.8
#if(1)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->GGD20();
			test->inset();
			if (test->DetectPfa(Phi[i]))countPfa++;
			if (test->DetectPm(Phi[i]))countPm++;
			delete test;
		}
		//cout << countPfa << "  " << countPm << endl;
		ExpPfa[i] = (double) countPfa / 1000000.0;
		ExpPm[i] = (double)countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	//无攻击情况
	//c=1.0
	//a=1.8
#if(0)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->GGD10();
			test->inset();
			countPfa += test->DetectPfa(Phi[i]);
			countPm += test->DetectPm(Phi[i]);
			delete test;
		}
		ExpPfa[i] = countPfa / 1000000.0;
		ExpPm[i] = countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	//无攻击情况
	//c=0.5
	//a=1.8
#if(0)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->GGD05();
			test->inset();
			countPfa += test->DetectPfa(Phi[i]);
			countPm += test->DetectPm(Phi[i]);
			delete test;
		}
		ExpPfa[i] = countPfa / 1000000.0;
		ExpPm[i] = countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	//无攻击情况
	//c=2.0
	//a=1.5
#if(0)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->GGD20();
			test->inset(1.5);
			countPfa += test->DetectPfa(Phi[i]);
			countPm += test->DetectPm(Phi[i]);
			delete test;
		}
		ExpPfa[i] = countPfa / 1000000.0;
		ExpPm[i] = countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	//受攻击情况
	//STD=2.5
#if(0)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->Gauss();
			test->inset();
			test->attack(2.5);
			countPfa += test->DetectPfa(Phi[i]);
			countPm += test->DetectPm(Phi[i]);
			delete test;
		}
		ExpPfa[i] = countPfa / 1000000.0;
		ExpPm[i] = countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	//受攻击情况
	//STD=5
#if(0)
	for (int i = 0; i < M; i++)
	{
		countPm = 0;
		countPfa = 0;
		for (int j = 0; j < 1000000; j++)
		{
			test = new MonteCarlo;
			test->Gauss();
			test->inset();
			test->attack(5);
			countPfa += test->DetectPfa(Phi[i]);
			countPm += test->DetectPm(Phi[i]);
			delete test;
		}
		ExpPfa[i] = countPfa / 1000000.0;
		ExpPm[i] = countPm / 1000000.0;
	}

	out << "实验误检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPfa[i] << "  ";
	out << endl;

	out << "实验漏检率为" << endl;
	for (int i = 0; i < M; i++)
		out << ExpPm[i] << "  ";
	out << endl;
#endif

	return 0;
    
}