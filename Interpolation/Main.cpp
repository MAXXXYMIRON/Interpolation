#include<iostream>
#include<vector>

using namespace std;
typedef vector<vector<float>> Coordinate;

//Интерполяция по Лагранжу
float Ln(const Coordinate &points, float x)
{
	float Lag = 0;
	unsigned n = points.size();
	float numerator,
		denumerator;

	for (unsigned k = 0; k < n; k++)
	{
		numerator = 1;
		for (unsigned i = 0; i < n; i++)
			if (i != k) numerator *= x - points[i][0];

		denumerator = 1;
		for (unsigned i = 0; i < n; i++)
			if (i != k) denumerator *= points[k][0] - points[i][0];

		Lag += points[k][1] * (numerator / denumerator);
	}

	return Lag;
}

//Разделённые разности
Coordinate DivSub(const Coordinate &points)
{
	unsigned n = points.size();

	Coordinate y;
	y.resize(n);
	for (unsigned i = 0; i < y.size(); i++)
		y[i].resize(n);

	for (unsigned i = 0; i < n; i++)
	{
		y[i][0] = points[i][1];
	}

	for (unsigned m = 1; m < n; m++)
	{
		for (unsigned k = 0; k < n - m; k++)
		{
			y[k][m] = (y[k + 1][m - 1] - y[k][m - 1]) / (points[k + m][0] - points[k][0]);
		}
	}

	return y;
}

//Интерполяция по Ньютону (вперёд)
float NFn(const Coordinate &points, float x)
{
	Coordinate y = DivSub(points);

	float N_forward = points[0][1],
		prod = 1;
	unsigned n = points.size();

	for (unsigned k = 1; k < n; k++)
	{
		prod *= x - points[k - 1][0];
		N_forward += y[0][k] * prod;
	}
	return N_forward;
}

//Интерполяция по Ньютону (назад)
float NBn(const Coordinate &points, float x)
{
	Coordinate y = DivSub(points);

	unsigned n = points.size();

	float N_back = points[n - 1][1],
		prod = 1;

	for (unsigned k = 1; k < n; k++)
	{
		prod *= x - points[n - k][0];
		N_back += y[n - (k + 1)][k] * prod;
	}

	return N_back;
}


void main()
{
	Coordinate Points = { 
		{-1.8, 6.63552}, 
		{-0.3, -3.88773}, 
		{0.7, 16.99677}, 
		{0.9, 21.86919}, 
		{2.3, 15.99213}, 
		{3, 0} };

	float x = 1.8;

	cout << Ln(Points, x) << endl;
	cout << NFn(Points, x) << endl;
	cout << NBn(Points, x) << endl;

	system("pause");
}