#include <iostream>
#include <cmath>
using namespace std;
#define MAX 100

int num = 0;
double z, x, c, v, a, b;
int piece_time[MAX] = { 0 };
double w[MAX] = { 0 };
double W[MAX] = { 0 };
double P[MAX] = { 0 };
double T[MAX] = { 0 };
double t = 0;
double sum = 0;


double before(double r)
{
	double ret = num * c + (r - 1) * z;
	return ret;
}

double normal()
{
	double ret = num * v;
	return ret;
}

double delay(double r)
{
	double ret = (num + 1 - r) * x;
	return ret;
}

double getmin(double d1, double d2, double d3)
{
	double ret = (d1 < d2) ? d1 : d2;
	ret = (ret < d3) ? ret : d3;
	return ret;
}

double GetW(int r)
{
	if (r == num)
	{
		return  pow(r, a) * w[r - 1];
	}
	else
	{
		double xx = 0;
		for (int j = r; j < v; j++)
		{
			xx += GetW(j + 1);
		}
		return pow(r, a) * (w[r - 1] + b * xx);
	}
}

double Getp(int r)
{
	return (piece_time[r] + b * t) * pow(r + 1, a);
}

int main()
{
	cout << "请输入要加工的工件个数" << endl;
	cin >> num;
	if (!num)
	{
		cout << "工件个数为0！" << endl;
		return 0;
	}

	cout << "请输入加工各工件所需要的时间" << endl;
	for (int i = 0; i < num; ++i)
	{
		cin >> piece_time[i];
	}

	cout << "请按顺序输入参数α，β，δ，γ，a，b" << endl;
	cin >> z >> x >> c >> v >> a >> b;

	//w
	for (int r = 0; r < num; ++r)
	{
		double d1 = before(r + 1);
		double d2 = normal();
		double d3 = delay(r + 1);
		w[r] = getmin(d1, d2, d3);
	}

	//W
	for (int r = 0; r < num; ++r)
	{
		W[r] = GetW(r + 1);
		cout << "r = " << r << " Wr = " << W[r] << endl;
	}

	for (int r = 0; r < num; ++r)
	{
		P[r] = Getp(r);
		t += P[r];
		T[r] = t;
	}

	system("pause");
	cout << "总的时间成本为：" << sum << endl;

	return 0;
}