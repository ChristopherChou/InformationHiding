#pragma once
#include<string>
#include"DCT.h"

//w����
const int w[34] = { -1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								-1,1,-1,1,1,-1,1,-1,
								1,-1,1,-1,-1,1,-1,1,
								1,-1	};

class SS
{
private:
	//ֱ�Ӷ����ά����ᵼ��ջ��������Ըĳ���һά����Ķ��Ϸ���
	//double picture[512][512];
	//double picture_inset[512][512];
	double *picture;
	double *picture_inset;
	int logo[64][8];
	//int logo_inset[64 * 64];
	int* logo_inset;
	//int logo_decode[64 * 64];
	int* logo_decode;
	//unsigned char picBuf[512 * 512];
	unsigned char *picBuf;
	unsigned char logoBuf[512];
public:
	SS();//��Ҫ���пռ�ķ���
	~SS();
	int RunAll();
	//int inset(double picture[512][512], double picture_inset[512][512], int logo[4096], int k, double strength);
	int inset(double* picture, double* picture_inset, int *logo, double strength);//���ˮӡ��Ƕ��
	int inset8x8(double pic[8][8], double strength, int b);//��8x8�Ŀ����Ƕ��
	int decode(double* picture_inset, int* logo_decode);//ˮӡ����
	int compare(int* logo_inset, int* logo_decode);//�Ƚϼ��������
	int decode8x8(double block[8][8]);//��8x8�Ŀ���н���
	int transfer(int* logo_decode, unsigned char* logo_buf);//��logoͼתΪλ����ʽ
};

