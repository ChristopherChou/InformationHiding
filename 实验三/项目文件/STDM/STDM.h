#pragma once
#include<string>
#include"DCT.h"

//w����
const int w[34] = { -1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								-1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								1,-1 };

class STDM
{
private:
	//ֱ�Ӷ����ά����ᵼ��ջ��������Ըĳ���һά����Ķ��Ϸ���
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
	double delta;//��������
public:
	STDM();//��Ҫ���пռ�ķ���
	~STDM();
	int RunAll();
	//���ˮӡ��Ƕ��
	int inset(double* picture, double* picture_inset, int* logo);
	//UPDATE1
	int inset8x8(double pic[8][8], int b);//��8x8�Ŀ����Ƕ��
	int decode(double* picture_inset, int* logo_decode);//ˮӡ����
	int compare(int* logo_inset, int* logo_decode);//�Ƚϼ��������
	//UPDATE2
	int decode8x8(double block[8][8]);//��8x8�Ŀ���н���
	//��logoͼתΪλ����ʽ
	int transfer(int* logo_decode, unsigned char* logo_buf);
};

