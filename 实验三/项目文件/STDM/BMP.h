#pragma once
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<vector>
//class Bmp
//ֱ��ʹ���˵ڶ��ε�ʵ��
class Bmp
{
private:

public:
	unsigned char* pBmpBuf;//����ͼ�����ݵ�ָ��
	int bmpWidth;//��
	int bmpHeight;//��
	RGBQUAD* pColorTable;//��ɫ��ָ��
	int biBitCount;//ͼ�����ͣ�ÿ����λ��
	int readBmp(const char* bmpName);//��ȡͼ���λͼ����
	int saveBmp(const char* bmpName, unsigned char* imgBuf, int width, int height, int biBItCount, RGBQUAD* pColorTable);//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
};

