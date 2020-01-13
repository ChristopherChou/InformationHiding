#include "SS.h"
#include"Bmp.h"

using namespace std;

SS::SS()
{
	picture = new double[512 * 512];
	picture_inset = new double[512 * 512];
	picBuf = new unsigned char[512 * 512];
	logo_inset = new int[64 * 64];
	logo_decode = new int[64 * 64];
}

SS::~SS()
{
	delete[]picBuf;
	delete[]picture_inset;
	delete[]picture;
	delete[]logo_inset;
	delete[]logo_decode;
}

int SS::RunAll()
{
	//打开Lena图
	Bmp lena;
	if (lena.readBmp("LENA.BMP")==0)
		cout << "LENA.BMP打开成功" << endl;
	else {
		cout << "LENA.BMP打开失败";
		return -1;
	}
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
		{
			//picture[i][j] = (*lena.pBmpBuf);
			picture[512 * i + j]=(*lena.pBmpBuf);
			//picture_inset[i][j] = picture[i][j];
			picture_inset[512 * i + j] = picture[512 * i + j];
			lena.pBmpBuf++;
		}

	//打开Logo
	Bmp Logo;
	if(Logo.readBmp("LOGO.BMP")==0)
		cout << "LOGO.BMP打开成功" << endl;
	else {
		cout << "LOGO.BMP打开失败";
		return -1;
	}
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 8; j++)
		{
			logo[i][j] = (int)(*Logo.pBmpBuf);
			Logo.pBmpBuf++;
		}
	//把位图LOGO读出
	int count = 0;
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 8; j++)
		{
			int a;
			a =logo[i][j];
			for (int k = 0; k < 8; k++)
			{
				logo_inset[7 - k + count * 8] = ((a >> k) & 0x01);//把每一位读出
				//if (logo_inset[7 - k + count * 8] == 0)
					//logo_inset[7 - k + count * 8] = -1; 
			}
			count++;
		}

	int lineByteLena = (lena.bmpWidth * lena.biBitCount / 8 + 3) / 4 * 4;
	int lineByteLogo= (Logo.bmpWidth * Logo.biBitCount / 8 + 3) / 4 * 4;
	
	double strength;//嵌入强度
	cout << "请输入嵌入强度";
	cin >> strength;

	//嵌入水印
	inset(picture, picture_inset, logo_inset, strength);

	//保存图片
	int count_out = 0;
	for (int i = 0; i < 512; i++)  
		for (int j = 0; j < 512; j++)
		{
			//picBuf[count_out] = (unsigned char)picture_inset[i][j];
			picBuf[count_out] = (unsigned char)picture_inset[512*i+j];
			count_out++;
		}
	if (lena.saveBmp("LenaInset.BMP", picBuf, lena.bmpWidth,lena.bmpHeight , lena.biBitCount, lena.pColorTable)==0)
		cout << "嵌入图片保存成功" << endl;
	else
	{
		cout << "嵌入图片保存失败"; exit(-1);
	}

	cout << "请输入需要解码的图片路径(受到攻击后):";
	string path;
	cin >> path;
	Bmp lena_inset;
	if (lena_inset.readBmp(path.c_str()) == 0)
		cout << path<<"打开成功" << endl;
	else {
		cout << path<<"打开失败";
		return -1;
	}
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; j++)
		{
			picture_inset[512 * i + j] = (*lena_inset.pBmpBuf);
			lena_inset.pBmpBuf++;
		}
	
	//解码
	decode(picture_inset,logo_decode);

	//计算错误率
	compare(logo_inset, logo_decode);

	//保存解码的图像
	transfer(logo_decode, logoBuf);
	Logo.saveBmp("LogoDecode.BMP", logoBuf, Logo.bmpWidth, Logo.bmpHeight, Logo.biBitCount, Logo.pColorTable);
	cout << "解码的图像已保存到LogoDecode.BMP" << endl;
	return 0;
}

int SS::inset(double* picture, double* picture_inset, int*logo,  double strength)
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
					block[m][n] = picture[(i + m)*512+j + n];
			b = logo[count_logo];//要嵌入的0/1
			count_logo++;    

			//对每一个块进行嵌入
			inset8x8(block, strength, b);

			for (m = 0; m < 8; m++)
				for (n = 0; n < 8; n++)
					//picture_inset[i + m][j + n] = block[m][n];
					picture_inset[(i + m)*512+j + n] = block[m][n];
		}
	return 0;
}

int SS::inset8x8(double pic[8][8], double strength, int b)
{
	DCT d;
	//dct正变换
	double pic_dct[8][8];
	d.DiscreteCosineTransform(pic, pic_dct);

	//提取dct系数
	//暂定为8，斜对角线(比较简单)
	//修改为34，斜着的5行
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


	//嵌入
	for (int i = 0; i < 34; i++)
		zig[i] += strength*(b ? 1 : -1) * w[i] ;

	//
	zig_count = 0;
	for (int i = 0; i < 6; i++)
	{
		pic_dct[i][5 - i]=zig[zig_count] ;
		zig_count++;
	}
	for (int i = 0; i < 7; i++)
	{
		pic_dct[i][6 - i]=zig[zig_count] ;
		zig_count++;
	}
	for (int i = 0; i < 8; i++)
	{
		pic_dct[i][7 - i]=zig[zig_count] ;
		zig_count++;
	}
	for (int i = 1; i < 8; i++)
	{
		pic_dct[i][8 - i]=zig[zig_count] ;
		zig_count++;
	}
	for (int i = 2; i < 8; i++)
	{
		pic_dct[i][9 - i]=zig[zig_count] ;
		zig_count++;
	}

	//反变换
	d.InverseDiscreteCosineTransform(pic_dct, pic);

	return 0;
}

int SS::decode(double* picture_inset, int* logo_decode)
{
	int i, j, m, n;
	int count_logo = 0;
	int b;//解码得到的数据
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

int SS::compare(int* logo_inset, int* logo_decode)
{
	int count = 0;
	for (int i = 0; i < 4096; i++)
		if (logo_inset[i] != logo_decode[i])
			count++;
	cout << "解码错误率为：" << (count / 4096.0) << endl;
	return 0;
}

int SS::decode8x8(double block[8][8])
{
	DCT d;
	double x[8][8];
	double test=0;
	d.DiscreteCosineTransform(block, x);

	int count = 0;

	//解码也需要修改
	for (int i = 0; i < 6; i++)
	{
		test += x[i][5 - i] * w[count];
		count++;
	}
	for (int i = 0; i < 7; i++)
	{
		test += x[i][6 - i] * w[count];
		count++;
	}
	for (int i = 0; i < 8; i++)
	{
		test += x[i][7 - i] * w[count];
		count++;
	}
	for (int i = 1; i < 8; i++)
	{
		test += x[i][8 - i] * w[count];
		count++;
	}
	for (int i = 2; i < 8; i++)
	{
		test += x[i][9 - i] * w[count];
		count++;
	}

	if (test > 0)return 1;
	else return 0;
}

int SS::transfer(int* logo_decode, unsigned char* logo_buf)
{
	int count = 0;
	for (int i = 0; i < 512;i++)
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
