#include <iostream>
#include <string>
#include <vector>
#include <complex>
using namespace std;
const double pi = 3.1415926535897932384626433832795;
const char DNK[4] = { 'A', 'G', 'T', 'C' };

void fft(vector<complex<double>> &a)
{
	int n = a.size();
	if (n == 1)
		return;
	vector<complex<double>> aLeft(n / 2), aRight(n / 2);
	for (int i = 0; i < n; ++i)
	if (i % 2 == 0)
		aLeft[i / 2] = a[i];
	else
		aRight[(i - 1) / 2] = a[i];

	fft(aLeft);
	fft(aRight);
	double phi = 2 * pi / n;
	complex<double> w=complex<double>(1, 0);
	complex<double> wk(cos(phi), sin(phi));

	for (int i = 0; i < n / 2; ++i)
	{
		a[i] = aLeft[i] + w * aRight[i];
		a[n / 2 + i] = aLeft[i] - w* aRight[i];

		w *= wk;
	}
}
void ifft(vector<complex<double>> &a)
{
	int n = a.size();
	if (n == 1)
		return;
	vector<complex<double>> aLeft(n / 2), aRight(n / 2);
	for (int i = 0; i < n; ++i)
	if (i % 2 == 0)
		aLeft[i / 2] = a[i];
	else
		aRight[(i - 1) / 2] = a[i];

	ifft(aLeft);
	ifft(aRight);
	double phi = -2 * pi / n;
	complex<double> w=complex<double>(1, 0);
	complex<double> wk(cos(phi), sin(phi));


	for (int i = 0; i < n / 2; ++i)
	{
		a[i] = (aLeft[i] + w * aRight[i]) *0.5;
		a[n / 2 + i] = (aLeft[i] - w * aRight[i]) *0.5;
		w *= wk;
	}
}
vector<int> multipl(vector<int> A, vector<int> B)
{
	vector<complex<double>> furA, furB;
	furA.assign(A.size() * 2, complex<double>(0, 0));
	furB.assign(A.size() * 2, complex<double>(0, 0));
	for (int i = A.size(); i < A.size() * 2; ++i)
	{
		furA[i] = complex<double>(A[i - A.size()], 0);
		furB[i] = complex<double>(B[i - A.size()], 0);
	}
	for (int i = 0; i < furB.size() / 2; ++i)
	{
		swap(furB[i], furB[furB.size() - i - 1]);
	}
	fft(furA);
	fft(furB);
	
	for (int i = 0; i < furA.size(); ++i)
		furA[i] *= furB[i];

	ifft(furA);
	vector<int> res(2 * A.size() - 1);
	for (int i = 0; i < res.size(); ++i)
	{
		res[i] = (char)(furA[i].real() + 0.5);
	}
	return res;
}
int main()
{
	int n;
	cin >> n;
	string StringA, StringB;
	cin >> StringA >> StringB;
	vector<int> A, B;

	vector<int> shift(n);
	for (int t = 0; t < 4; ++t)
	{
		for (int i = 0; i < StringA.size(); ++i)
		if (StringA[i] == DNK[t])
			A.push_back(1);
		else
			A.push_back(0);
		for (int i = 0; i < StringB.size(); ++i)
		if (StringB[i] == DNK[t])
			B.push_back(1);
		else
			B.push_back(0);
		n = A.size();
		vector<int> res = multipl(A, B);
		shift[0] += res[n - 1];
		for (int i = 1; i < n - 1; ++i)
			shift[i] += res[n - 1 + i] + res[i - 1];
		res.clear();
		A.clear();
		B.clear();
	}
	int max =0;
	for (int i = 0; i < shift.size(); ++i)
	{
		if (shift[max] < shift[i])
			max = i;
	}
	cout << shift[max] << " " << max;
	cin >> n;

}