#pragma once
#include<math.h>
#include<iostream>
#define NUM 8
#define PI 3.1415926

//class DCT 
//部分参考于https://blog.csdn.net/lwfcgz/article/details/8040550，但进行了较大修改
class DCT
{
private:

public:
	int round(double a);//修正函数，只在反变换时候进行修正
	void DiscreteCosineTransform(double input[NUM][NUM],double output[NUM][NUM]);//DCT正变换
	void InverseDiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM]);//DCT反变换
};

