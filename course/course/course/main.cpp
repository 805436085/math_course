#include <iostream>
using namespace std;

double before(int num_, double c_, double r_, double z_)
{
	double ret = num_ * c_ + (r_ - 1) * z_;
	return ret;
}

double normal(int num_, double v_)
{
	double ret = num_ * v_;
	return ret;
}

double delay(int num_, double r_, double x_)
{
	double ret = (num_ + 1 - r_) * x_;
	return ret;
}

double getmin(double a, double b, double c)
{
	double ret = (a < b) ? a : b;
	ret = (ret < c) ? ret : c;
	return ret;
}

double digui(int rr, double a, double b)
{

}

double Getssub(int rr, int r, double a)
{
	b*pow(rr, a)*pow(r, a);
}

double Getsub(int rr, int r, int n, double a, double b, double right[])
{
	double ret = b*pow(rr, a)*pow(r, a)*right[rr];
	int d = n - rr;
	if (d > 0)
	{
		rr++;
		Getssub(rr, r, a);
	}
	return ret;
}

double getW(int r,int n, double a, double b, double right[])
{
	int rr = r;
	double ret = pow(rr, a)*right[rr];
	int d = n - rr;
	if (d > 0)
	{
		rr++;
		ret += Getsub(rr, r, n, a, b, right);//7,6
	}

	return ret;
}

int main()
{
//#ifndef DEBUG
//#define DEBUG
//#endif

#ifdef DEBUG
	double a,b,c;
	double x, y;
	//cin >> a >> b >> c;
	//cout << getmin(a, b, c) << endl;
	cin >> x >> y;
	cout << pow(x, y) << endl;
#else
	double num = 0;
	cout << "请输入要加工的工件个数" << endl;
	cin >> num;
	if (!num)
	{
		cout << "工件个数为0！" << endl;
		return 0;
	}

	int piece_time[100] = { 0 };
	cout << "请输入加工各工件所需要的时间" << endl;
	for (int i = 0; i < num; ++i)
	{
		cin >> piece_time[i];
	}

	double z, x, c, v, b, n;
	cout << "请按顺序输入参数α，β，δ，γ，a，b" << endl;
	cin >> z >> x >> c >> v >> b >> n;

	double right[100] = { 0 };
	double Right[100] = { 0 };
	double sum = 0;
	for (int r = 0; r < num; ++r)
	{
		right[r] = getmin(before(num, c, r+1, z), normal(num, v), delay(num, r+1, x));
		//Right[r] = pow(num, b) * right[r];
		//sum += Right[r] * piece_time[r];
	}

	cout << "总的时间成本为：" << sum << endl;
#endif
	return 0;
}