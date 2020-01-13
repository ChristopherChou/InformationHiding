#pragma once
#include<string>
#include"DCT.h"

//w序列
const int w[34] = { -1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								-1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								1,-1 };

class STDM
{
private:
	//直接定义二维数组会导致栈溢出，所以改成了一维数组的堆上分配
	//double picture[512][512];
	//double picture_inset[512][512];
	double* picture;
	double* picture_inset;
	int logo[64][8];
	//int logo_inset[64 * 64];
	int* logo_inset;
	//int logo_decode[64 * 64];
	int* logo_decode;
	//unsigned char picBuf[512 * 512];
	unsigned char* picBuf;
	unsigned char logoBuf[512];
	double delta;//量化步长
public:
	STDM();//主要进行空间的分配
	~STDM();
	int RunAll();
	//完成水印的嵌入
	int inset(double* picture, double* picture_inset, int* logo);
	//UPDATE1
	int inset8x8(double pic[8][8], int b);//对8x8的块进行嵌入
	int decode(double* picture_inset, int* logo_decode);//水印解码
	int compare(int* logo_inset, int* logo_decode);//比较计算错误率
	//UPDATE2
	int decode8x8(double block[8][8]);//对8x8的块进行解码
	//把logo图转为位的形式
	int transfer(int* logo_decode, unsigned char* logo_buf);
};

