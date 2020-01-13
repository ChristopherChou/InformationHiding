#include "STDM.h"
#include"Bmp.h"

using namespace std;

STDM::STDM()
{
	picture = new double[512 * 512];
	picture_inset = new double[512 * 512];
	picBuf = new unsigned char[512 * 512];
	logo_inset = new int[64 * 64];
	logo_decode = new int[64 * 64];
}

STDM::~STDM()
{
	delete[]picBuf;
	delete[]picture_inset;
	delete[]picture;
	delete[]logo_inset;
	delete[]logo_decode;
}

int STDM::RunAll()
{
	//��Lenaͼ
	Bmp lena;
	if (lena.readBmp("LENA.BMP") == 0)
		cout << "LENA.BMP�򿪳ɹ�" << endl;
	else {
		cout << "LENA.BMP��ʧ��";
		return -1;
	}
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
		{
			//picture[i][j] = (*lena.pBmpBuf);
			picture[512 * i + j] = (*lena.pBmpBuf);
			//picture_inset[i][j] = picture[i][j];
			picture_inset[512 * i + j] = picture[512 * i + j];
			lena.pBmpBuf++;
		}

	//��Logo
	Bmp Logo;
	if (Logo.readBmp("LOGO.BMP") == 0)
		cout << "LOGO.BMP�򿪳ɹ�" << endl;
	else {
		cout << "LOGO.BMP��ʧ��";
		return -1;
	}
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 8; j++)
		{
			logo[i][j] = (int)(*Logo.pBmpBuf);
			Logo.pBmpBuf++;
		}
	//��λͼLOGO����
	int count = 0;
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 8; j++)
		{
			int a;
			a = logo[i][j];
			for (int k = 0; k < 8; k++)
			{
				logo_inset[7 - k + count * 8] = ((a >> k) & 0x01);//��ÿһλ����
				//if (logo_inset[7 - k + count * 8] == 0)
					//logo_inset[7 - k + count * 8] = -1; 
			}
			count++;
		}

	int lineByteLena = (lena.bmpWidth * lena.biBitCount / 8 + 3) / 4 * 4;
	int lineByteLogo = (Logo.bmpWidth * Logo.biBitCount / 8 + 3) / 4 * 4;

	//��������
	//double strength;//Ƕ��ǿ��
	cout << "��������������";
	cin >> delta;

	//Ƕ��ˮӡ
	inset(picture, picture_inset, logo_inset);

	//����ͼƬ
	int count_out = 0;
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
		{
			//picBuf[count_out] = (unsigned char)picture_inset[i][j];
			picBuf[count_out] = (unsigned char)picture_inset[512 * i + j];
			count_out++;
		}
	if (lena.saveBmp("LenaInset.BMP", picBuf, lena.bmpWidth, lena.bmpHeight, lena.biBitCount, lena.pColorTable) == 0)
		cout << "Ƕ��ͼƬ����ɹ�" << endl;
	else
	{
		cout << "Ƕ��ͼƬ����ʧ��"; exit(-1);
	}

	cout << "��������Ҫ�����ͼƬ·��(�ܵ�������):";
	string path;
	cin >> path;
	Bmp lena_inset;
	if (lena_inset.readBmp(path.c_str()) == 0)
		cout << path << "�򿪳ɹ�" << endl;
	else {
		cout << path << "��ʧ��";
		return -1;
	}
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
		{
			picture_inset[512 * i + j] = (*lena_inset.pBmpBuf);
			lena_inset.pBmpBuf++;
		}

	//����
	decode(picture_inset, logo_decode);

	//���������
	compare(logo_inset, logo_decode);

	//��������ͼ��
	transfer(logo_decode, logoBuf);
	Logo.saveBmp("LogoDecode.BMP", logoBuf, Logo.bmpWidth, Logo.bmpHeight, Logo.biBitCount, Logo.pColorTable);
	cout << "�����ͼ���ѱ��浽LogoDecode.BMP" << endl;
	return 0;
}

int STDM::inset(double* picture, double* picture_inset, int* logo)
{
	int i, j, m, n;
	int count_logo = 0;
	int b;
	int count_w = 0;

	double block[8][8];
	for (i = 0; i < 512; i = i + 8)
		for (j = 0; j < 512; j = j + 8)
		{
			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					//block[m][n] =picture[i + m][j + n];
					block[m][n] = picture[(i + m) * 512 + j + n];
			b = logo[count_logo];//ҪǶ���0/1
			count_logo++;

			//��ÿһ�������Ƕ��
			inset8x8(block,  b);

			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					//picture_inset[i + m][j + n] = block[m][n];
					picture_inset[(i + m) * 512 + j + n] = block[m][n];
		}
	return 0;
}

//UPDATE1
int STDM::inset8x8(double pic[8][8], int b)
{
	DCT d;
	//dct���任
	double pic_dct[8][8];
	d.DiscreteCosineTransform(pic, pic_dct);

	//��ȡdctϵ��
	//�ݶ�Ϊ8��б�Խ���(�Ƚϼ�)
	//�޸�Ϊ34��б�ŵ�5��
	double zig[34];
	int zig_count = 0;
	for (int i = 0; i < 6; i++)
	{
		zig[zig_count] = pic_dct[i][5 - i];
		zig_count++;
	}
	for (int i = 0; i < 7; i++)
	{
		zig[zig_count] = pic_dct[i][6 - i];
		zig_count++;
	}
	for (int i = 0; i < 8; i++)
	{
		zig[zig_count] = pic_dct[i][7 - i];
		zig_count++;
	}
	for (int i = 1; i < 8; i++)
	{
		zig[zig_count] = pic_dct[i][8 - i];
		zig_count++;
	}
	for (int i = 2; i < 8; i++)
	{
		zig[zig_count] = pic_dct[i][9 - i];
		zig_count++;
	}


	//Ƕ��
	//d[0]=-delta/4
	//d[1]=delta/4
	//**************************************************************
	double x0 = 0;
	for (int i = 0; i < 34; i++)
		x0 += zig[i] * w[i];
	x0 /= 34;
	double q;
	//Ƕ��1
	if (b)
	{
		q = int((x0 - (delta / 4))/delta + 0.5) * delta + delta / 4;
	}
	//Ƕ��0
	else
	{
		q = int((x0 + (delta / 4))/delta + 0.5) * delta - delta / 4;
	}
	
	for (int i = 0; i < 34; i++)
		zig[i] += w[i] * (q - x0);
	

	//*************************************************************

	//
	zig_count = 0;
	for (int i = 0; i < 6; i++)
	{
		pic_dct[i][5 - i] = zig[zig_count];
		zig_count++;
	}
	for (int i = 0; i < 7; i++)
	{
		pic_dct[i][6 - i] = zig[zig_count];
		zig_count++;
	}
	for (int i = 0; i < 8; i++)
	{
		pic_dct[i][7 - i] = zig[zig_count];
		zig_count++;
	}
	for (int i = 1; i < 8; i++)
	{
		pic_dct[i][8 - i] = zig[zig_count];
		zig_count++;
	}
	for (int i = 2; i < 8; i++)
	{
		pic_dct[i][9 - i] = zig[zig_count];
		zig_count++;
	}

	//���任
	d.InverseDiscreteCosineTransform(pic_dct, pic);

	return 0;
}

int STDM::decode(double* picture_inset, int* logo_decode)
{
	int i, j, m, n;
	int count_logo = 0;
	int b;//����õ�������
	int count_w = 0;

	double block[8][8];
	for (i = 0; i < 512; i = i + 8)
		for (j = 0; j < 512; j = j + 8)
		{
			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					block[m][n] = picture_inset[(i + m) * 512 + j + n];
			logo_decode[count_logo] = decode8x8(block);
			count_logo++;
		}
	return 0;
}

int STDM::compare(int* logo_inset, int* logo_decode)
{
	int count = 0;
	for (int i = 0; i < 4096; i++)
		if (logo_inset[i] != logo_decode[i])
			count++;
	cout << "���������Ϊ��" << (count / 4096.0) << endl;
	return 0;
}

//UPDATE2
int STDM::decode8x8(double block[8][8])
{
	DCT d;
	double x[8][8];
	//double test = 0;
	d.DiscreteCosineTransform(block, x);

	int count = 0;

	//����
	//*********************************************************
	double y = 0;
	for (int i = 0; i < 6; i++)
	{
		y += x[i][5 - i] * w[count];
		count++;
	}
	for (int i = 0; i < 7; i++)
	{
		y+= x[i][6 - i] * w[count];
		count++;
	}
	for (int i = 0; i < 8; i++)
	{
		y += x[i][7 - i] * w[count];
		count++;
	}
	for (int i = 1; i < 8; i++)
	{
		y += x[i][8 - i] * w[count];
		count++;
	}
	for (int i = 2; i < 8; i++)
	{
		y += x[i][9 - i] * w[count];
		count++;
	}
	y /= 34;
	double q = int((y + delta / 4 )/delta+ 0.5) * delta - delta / 4;
	if (fabs(q - y) < delta / 4)
		return 0;
	else
		return 1;
	
}

int STDM::transfer(int* logo_decode, unsigned char* logo_buf)
{
	int count = 0;
	for (int i = 0; i < 512; i++)
	{
		logoBuf[count] = 0;
		for (int j = 0; j < 8; j++)
		{
			char c = 0;
			char c2;
			if (logo_decode[7 - j + count * 8] == 1)
			{
				c2 = ((c >> j) | 0x01) << j;
				logoBuf[count] |= c2;
			}
		}
		count++;
	}
	return 0;
}
