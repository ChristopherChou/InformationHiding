#pragma once
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<vector>
//class Bmp
//部分参考来自https://blog.csdn.net/lyy289065406/article/details/6717679
class Bmp
{
private:
	
public:
	unsigned char* pBmpBuf;//读入图像数据的指针
	int bmpWidth;//宽
	int bmpHeight;//高
	RGBQUAD* pColorTable;//颜色表指针
	int biBitCount;//图像类型，每像素位数
	int readBmp(const char* bmpName);//读取图像的位图数据
	int saveBmp(const char* bmpName, unsigned char* imgBuf, int width,int height, int biBItCount, RGBQUAD* pColorTable);//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
};

