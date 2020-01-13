#pragma once
#include<math.h>
#include<iostream>
#define NUM 8
#define PI 3.1415926

//class DCT 
//来自第二次实验
class DCT
{
private:

public:
	int round(double a);//修正函数，只在反变换时候进行修正
	//DCT正变换
	void DiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM]);
	//DCT反变换
	void InverseDiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM]);
};


