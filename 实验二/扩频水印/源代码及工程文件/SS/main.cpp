#include"DCT.h"
#include"SS.h"
using namespace std;

int main()
{
    SS s1;
    s1.RunAll();
    getchar();

    //dct变换TESTBEGIN
    if (0)
    {
        DCT test;
        short i = 0;
        short j = 0;
        short u = 0;
        short v = 0;
        // 8 x 8 的图像数据
        double input[8][8] =
        {
                  {89, 101, 114, 125, 126, 115, 105, 96},
                  {97, 115, 131, 147, 149, 135, 123, 113},
                  {114, 134, 159, 178, 175, 164, 149, 137},
                  {121, 143, 177, 196, 201, 189, 165, 150},
                  {119, 141, 175, 201, 207, 186, 162, 144},
                  {107, 130, 165, 189, 192, 171, 144, 125},
                  {97, 119, 149, 171, 172, 145, 117, 96},
                  {88, 107, 136, 156, 155, 129, 97, 75}
        };
        double output[8][8] = { 0 };
        test.DiscreteCosineTransform(input, output);
        cout << "The result of DCT:" << endl;

        for (u = 0; u < NUM; u++)
        {
            for (v = 0; v < NUM; v++)
            {
                cout << output[u][v] << "   ";
            }
            cout << endl;
        }

        test.InverseDiscreteCosineTransform(output, input);
        cout << "The result of IDCT:" << endl;
        for (i = 0; i < NUM; i++)
        {
            for (short j = 0; j < NUM; j++)
            {
                cout << input[i][j] << "  ";
            }
            cout << endl;
        }
    }
    //dct变换部分测试TESTEND


	return 0;
}
