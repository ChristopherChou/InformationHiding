#include "DCT.h"

//用来修正数据
int DCT::round(double a)
{
    if (a >= 255)return 255;
    else if (a <= 0)return 0;
    else return int(a + 0.5);
}

// DCT - Discrete Cosine Transform
void DCT::DiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM])
{
    double ALPHA, BETA;
    short u = 0;
    short v = 0;
    short i = 0;
    short j = 0;

    for (u = 0; u < NUM; u++)
    {
        for (v = 0; v < NUM; v++)
        {
            if (u == 0)
            {
                ALPHA = sqrt(1.0 / NUM);
            }
            else
            {
                ALPHA = sqrt(2.0 / NUM);
            }

            if (v == 0)
            {
                BETA = sqrt(1.0 / NUM);
            }
            else
            {
                BETA = sqrt(2.0 / NUM);
            }

            double tmp = 0.0;
            for (i = 0; i < NUM; i++)
            {
                for (j = 0; j < NUM; j++)
                {
                    tmp += input[i][j] * cos(( i*2.0 + 1) * u * PI / (2.0 * NUM)) * cos(( j*2.0 + 1) * v * PI / (2.0 * NUM));
                }
            }
            //output[u][v] = round(ALPHA * BETA * tmp);
            output[u][v] = (ALPHA * BETA * tmp);
        }
    }
}

// Inverse DCT
void DCT::InverseDiscreteCosineTransform(double input[NUM][NUM], double output[NUM][NUM])
{
    double ALPHA, BETA;
    short u = 0;
    short v = 0;
    short i = 0;
    short j = 0;

    for (i = 0; i < NUM; i++)
    {
        for (short j = 0; j < NUM; j++)
        {
            double tmp = 0.0;
            for (short u = 0; u < NUM; u++)
            {
                for (v = 0; v < NUM; v++)
                {
                    if (u == 0)
                    {
                        ALPHA = sqrt(1.0 / NUM);
                    }
                    else
                    {
                        ALPHA = sqrt(2.0 / NUM);
                    }
                    if (v == 0)
                    {
                        BETA = sqrt(1.0 / NUM);
                    }
                    else
                    {
                        BETA = sqrt(2.0 / NUM);
                    }
                    tmp += ALPHA * BETA * input[u][v] * cos(( i*2.0 + 1) * u * PI / (2.0 * NUM)) * cos((j*2.0 + 1) * v * PI / (2.0 * NUM));
                }
            }
            output[i][j] = round(tmp);
        }
    }
}


