#include "MonteCarlo.h"
#include<cstdlib>

MonteCarlo::MonteCarlo()
{
	X = new double[N];
	S0 = new double[N];
	S1 = new double[N];
	W = new int[N];
	//初始化W
	for (int i = 0; i < N ; i=i+2)
		W[i] = 1;
	for (int i = 1; i < N; i=i+2)
		W[i] = -1;
}

MonteCarlo::~MonteCarlo()
{
	delete[]X;
	delete[]S0;
	delete[]S1;
	delete[]W;
}

double MonteCarlo::ierfc(const double y)
// inverse of the error function erfc
// Copyright(C) 1996 Takuya OOURA (email: ooura@mmm.t.u-tokyo.ac.jp)
{
	const double IERFC_LIM = 27;
	double z = (y > 1) ? 2 - y : y;
	if (z < 1e-300) return (y > 1) ? -IERFC_LIM : IERFC_LIM;
	double w = 0.916461398268964 - log(z);
	double u = sqrt(w);
	double s = (log(u) + 0.488826640273108) / w;
	double t = 1 / (u + 0.231729200323405);
	double x = u * (1 - s * (s * 0.124610454613712 + 0.5)) -
		((((-0.0728846765585675 * t + 0.269999308670029) * t +
			0.150689047360223) * t + 0.116065025341614) * t +
			0.499999303439796) * t;
	t = 3.97886080735226 / (x + 3.97886080735226);
	u = t - 0.5;
	s = (((((((((0.00112648096188977922 * u +
		1.05739299623423047e-4) * u - 0.00351287146129100025) * u -
		7.71708358954120939e-4) * u + 0.00685649426074558612) * u +
		0.00339721910367775861) * u - 0.011274916933250487) * u -
		0.0118598117047771104) * u + 0.0142961988697898018) * u +
		0.0346494207789099922) * u + 0.00220995927012179067;
	s = ((((((((((((s * u - 0.0743424357241784861) * u -
		0.105872177941595488) * u + 0.0147297938331485121) * u +
		0.316847638520135944) * u + 0.713657635868730364) * u +
		1.05375024970847138) * u + 1.21448730779995237) * u +
		1.16374581931560831) * u + 0.956464974744799006) * u +
		0.686265948274097816) * u + 0.434397492331430115) * u +
		0.244044510593190935) * t -
		z * exp(x * x - 0.120782237635245222);
	x += s * (x * s + 1);
	return (y > 1) ? -x : x;
}

int MonteCarlo::GGD05()
{
	double* num1, *num2;
	num1 = new double[N];
	num2 = new double[N];
	random_device rd;
	mt19937_64 generator(rd());
	exponential_distribution<double> distribution(1.0);

	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		num1[i] = number;
	}
	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		num2[i] = number;
	}
	srand((int)1); 
	for (int i = 0; i < N; i++)
	{
		X[i] = pow(num1[i] + num2[i], 2);
		X[i] = rand() % 2 ? X[i] : -X[i];
	//	cout << X[i] << endl;
	}
	return 0;
}

int MonteCarlo::GGD10()
{
	random_device rd;
	mt19937_64 generator(rd());
	exponential_distribution<double> distribution(1.0);
	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		X[i] = number; 
		//cout << X[i] << endl;
	}
	srand((unsigned)time(0));
	for (int i = 0; i < N; i++)
	{
		X[i] = rand() % 2 ? X[i] : -X[i];
	}
	return 0;
}

int MonteCarlo::GGD20()
{
	//const int nrolls = 10000;  // number of experiments
	//const int nstars = 100;    // maximum number of stars to distribute
	random_device rd;
	mt19937_64 generator(rd());
	normal_distribution<double> distribution(0, 10.0);

	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		X[i] = number;
	}
	return 0;
}

int MonteCarlo::Gauss()
{
	random_device rd;
	mt19937_64 generator(rd());
	normal_distribution<double> distribution(0, 10.0);

	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		X[i] = number;
	}
	return 0;
}

int MonteCarlo::inset(double a)
{
	for (int i = 0; i < N; i++)
	{
		S1[i] = X[i] + a * W[i];  //嵌入水印
		S0[i] = X[i];  //不嵌入水印,用来统计漏检概率
	}
	return 0;
}

int MonteCarlo::DetectPm(double test)
{
	double temp=0;
	for (int i = 0; i < N; i++)
		temp += S1[i] * W[i];
	temp = temp / N;
	//cout << temp << endl;
	if (temp < test)  //漏检
		return 1;
	else
		return 0;
}

int MonteCarlo::DetectPfa(double test)
{
	double  temp=0;
	for (int i = 0; i < N; i++)
		temp+= S0[i] * W[i];  //不嵌入水印的线性相关器计算,统计误检概率
	temp= temp / N;
	if (temp >= test)  //误检
		return 1;
	else
		return 0;
}

double MonteCarlo::CaculateTest(const double x)
{
	return 10 * ierfc(x) *sqrt(2) / sqrt(N);
}

double MonteCarlo::CaculatePm(const double x,double a)
{
	return 1 - erfc(ierfc(x) *sqrt(2) - (sqrt(N) * a) / 10) /2;
	//我又看了一遍好像没问题...
}

int MonteCarlo::attack(double STD)
{
	double* V;
	V = new double[N];
	random_device rd;
	mt19937_64 generator(rd());
	normal_distribution<double> distribution(0, STD);
	for (int i = 0; i < N; ++i) {
		double number = distribution(generator);
		V[i] = number;
	}
	for (int i = 0; i < N; i++)
	{
		S0[i] += V[i];
		S1[i] += V[i];
	}
	delete[]V;
	return 0;
}

