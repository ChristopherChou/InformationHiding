#include"RandomNumber.h"
#include<iostream>

int main()
{
	RandomNumber rn;
	//均匀分布
	rn.uniformDistribution();

	//指数分布
	double beta;
	std::cout << "输入指数分布beta的值" << std::endl;
	std::cin >> beta;
	rn.expDistribution(beta);
	rn.expBeta();

	//高斯分布
	rn.gaussDstribution();
	rn.gaussExpectation();
	rn.gaussVar();

	
	//GGD分布
	std::cout << "输入GGD分布c=1.0时 beta的值" << std::endl;
	std::cin >> beta;
	rn.GGD10(beta);

	std::cout << "输入GGD分布c=0.5时 beta的值" << std::endl;
	std::cin >> beta;
	rn.GGD05(beta);

	return 0;

}