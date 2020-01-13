#define _CRT_SECURE_NO_WARNINGS
#include "Bmp.h"
using namespace std;


int Bmp::readBmp(const char* bmpName)
{
    FILE* fp = fopen(bmpName, "rb");   
    if (fp == NULL)
    {
        cout << "���ļ�ʧ��" << endl;
        return -1;
    }

    fseek(fp, sizeof(BITMAPFILEHEADER), 0); //����BMP�ļ�ͷ

    BITMAPINFOHEADER head; //BMP�ļ�ͷ
    fread(&head, sizeof(BITMAPINFOHEADER), 1, fp); //��ȡͼ����ߡ�ÿ������ռλ��

    bmpWidth = head.biWidth;
    bmpHeight = head.biHeight;
    biBitCount = head.biBitCount;

    //����ͼ��ÿ��������ռ�ֽ�����������4�ı�����
    int lineByte;
    lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
    
    if (biBitCount == 8)
    {
        //������ɫ������ռ䣬����ɫ���ڴ�
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }
    else if (biBitCount == 1)  
    {
        pColorTable = new RGBQUAD[2];
        fread(pColorTable, sizeof(RGBQUAD), 2, fp);
    }
    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

    fclose(fp); 
    return 0;
}

int Bmp::saveBmp(const char* bmpName, unsigned char* imgBuf, int width, int height, int biBItCount, RGBQUAD* pColorTable)
{
    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0
    int colorTablesize = 0; 
    if (biBitCount == 8)
        colorTablesize = 1024;

    //���洢ͼ������ÿ���ֽ���Ϊ4�ı���
    int lineByte;
    lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

    //���ļ�
    FILE* fp = fopen(bmpName, "wb");
    if (fp == NULL)
    {
        cout << "���ļ�ʧ��" << endl;
        return -1;
    }

    //BMP�ļ�ͷ
    BITMAPFILEHEADER filehead; 
    filehead.bfType = 0x4D42;//bmp����
    //bfSize��ͼ���ļ�4�������֮��
    filehead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
    filehead.bfReserved1 = 0;
    filehead.bfReserved2 = 0;
    filehead.bfOffBits = 54 + colorTablesize;//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
    fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//д�ļ�ͷ���ļ�

    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
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
    fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp); //дλͼ��Ϣͷ

    //����Ҷ�ͼ������ɫ��д���ļ�
    if (biBitCount == 8)
        fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);  

    else if (biBitCount == 1)  
    {
        fwrite(pColorTable, sizeof(RGBQUAD), 2, fp);
    }

    //дλͼ���ݽ��ļ�
    fwrite(imgBuf, lineByte * height, 1, fp); 

    fclose(fp);    
    return 0;
}
