#include "Audio\Headers\AudioFile.h"
#include "Audio\Headers\fft.h"
#include "Audio\Headers\fft_settings.h"
#include <complex>
#include <iostream>

using namespace std;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

CArray Sampling(char* filename, int& sample)
{
	AudioFile<double> audiofile;
	Complex* timesaples;
	
	audiofile.load(string(filename));
	int channel = 0;
	int numSamples = sample = audiofile.getNumSamplesPerChannel();
	
	timesamples = new Complex[numSamples/100];
	for(int i = 0 ; i< numSamples; i++)
	{
		double currentSample = audiofile.samples[channel][i];
		timesmaples[i] = currentSample;
	}
	
	CArray data(timesamples,numSamples/100);
	// FFT - To Do...
	//return data;
}