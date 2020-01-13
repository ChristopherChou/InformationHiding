#define _CRT_SECURE_NO_WARNINGS
#include "Bmp.h"
using namespace std;


int Bmp::readBmp(const char* bmpName)
{
    FILE* fp = fopen(bmpName, "rb");   
    if (fp == NULL)
    {
        cout << "打开文件失败" << endl;
        return -1;
    }

    fseek(fp, sizeof(BITMAPFILEHEADER), 0); //跳过BMP文件头

    BITMAPINFOHEADER head; //BMP文件头
    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp); //读取图像宽、高、每像素所占位数

    bmpWidth = head.biWidth;
    bmpHeight = head.biHeight;
    biBitCount = head.biBitCount;

    //计算图像每行像素所占字节数（必须是4的倍数）
    int lineByte;
    lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
    
    if (biBitCount == 8)
    {
        //申请颜色表所需空间，读颜色进内存
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }
    else if (biBitCount == 1)  
    {
        pColorTable = new RGBQUAD[2];
        fread(pColorTable, sizeof(RGBQUAD), 2, fp);
    }
    //申请位图数据所需要的空间，读位图数据进内存
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

    fclose(fp); 
    return 0;
}

int Bmp::saveBmp(const char* bmpName, unsigned char* imgBuf, int width, int height, int biBItCount, RGBQUAD* pColorTable)
{
    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
    int colorTablesize = 0; 
    if (biBitCount == 8)
        colorTablesize = 1024;

    //待存储图像数据每行字节数为4的倍数
    int lineByte;
    lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

    //打开文件
    FILE* fp = fopen(bmpName, "wb");
    if (fp == NULL)
    {
        cout << "打开文件失败" << endl;
        return -1;
    }

    //BMP文件头
    BITMAPFILEHEADER filehead; 
    filehead.bfType = 0x4D42;//bmp类型
    //bfSize是图像文件4部分组成之和
    filehead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
    filehead.bfReserved1 = 0;
    filehead.bfReserved2 = 0;
    filehead.bfOffBits = 54 + colorTablesize;//bfOffBits是图像文件前3个部分所需空间之和
    fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//写文件头进文件

    //申请位图信息头结构变量，填写信息头信息
    BITMAPINFOHEADER head;
    head.biBitCount = biBitCount;
    head.biClrImportant = 0;
    head.biClrUsed = 0;
    head.biCompression = 0;
    head.biHeight = height;
    head.biPlanes = 1;
    head.biSize = 40;
    head.biSizeImage = lineByte * height;
    head.biWidth = width;
    head.biXPelsPerMeter = 0;
    head.biYPelsPerMeter = 0;
    fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp); //写位图信息头

    //如果灰度图像，有颜色表，写进文件
    if (biBitCount == 8)
        fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);  

    else if (biBitCount == 1)  
    {
        fwrite(pColorTable, sizeof(RGBQUAD), 2, fp);
    }

    //写位图数据进文件
    fwrite(imgBuf, lineByte * height, 1, fp); 

    fclose(fp);    
    return 0;
}
