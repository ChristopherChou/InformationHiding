#include"RandomNumber.h"
#include<iostream>

int main()
{
	RandomNumber rn;
	//���ȷֲ�
	rn.uniformDistribution();

	//ָ���ֲ�
	double beta;
	std::cout << "����ָ���ֲ�beta��ֵ" << std::endl;
	std::cin >> beta;
	rn.expDistribution(beta);
	rn.expBeta();

	//��˹�ֲ�
	rn.gaussDstribution();
	rn.gaussExpectation();
	rn.gaussVar();

	
	//GGD�ֲ�
	std::cout << "����GGD�ֲ�c=1.0ʱ beta��ֵ" << std::endl;
	std::cin >> beta;
	rn.GGD10(beta);

	std::cout << "����GGD�ֲ�c=0.5ʱ beta��ֵ" << std::endl;
	std::cin >> beta;
	rn.GGD05(beta);

	return 0;

}