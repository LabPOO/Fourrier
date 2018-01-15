#include <iostream>
#include <valarray>
#include <complex>

using namespace std;
const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

void fft(std::valarray<std::complex<double>> &x)
{
	const size_t N = x.size();
	if (N<= 1) return;
	
	std::valarray<Complex> even = x[std::slice(0,N/2,2)];
	std::valarray<Complex> odd = x [std::slice(1,N/2,2)];
	
	fft(even);fft(odd);
	
	for(size_t k = 0; k< N/2; ++k)
	{
		Complex t = std::polar(1.0,-2*PI*k/N)*odd[k];
		x[k] = even[k] +t;
		x[k+N/2] = even[k] -t;
	}
}