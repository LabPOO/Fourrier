//============================//
#include "Head\AudioFile.h"
#include "Head\fft.h"
#include "Head\fft_settings.h"
/**
    Librarii de manipulare a fisierelor audio
    https://github.com/adamstark/AudioFile
**/
//============================//
#include <stdio.h>
#include <valarray>
#include <complex>
#include <fstream>
#include <iomanip>
/**
    Librarii standard C++ pentru numere complexe , input/output
    consola/fisiere, manipulare de date, si manipularea datelor de iesire
**/
//============================//
using namespace std;
const double PI = 3.141592653589793238460;
//============================//
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
/**
    Am creat un "alias" pentru tipurile de date complexe si pentru
    vectorii de date complexe, pentru a putea fi usor de utilizat
    si usor de inteles
**/
//============================//
void fft(std::valarray<std::complex<double>> &x);
CArray Sampling(char* filename,int& sample);
double distance(Complex input,Complex compare);
/**
    Prototipuri de functii:
        - void fft(std::valarray<std::complex<double>> &x)
            Functia aplica algoritmul FFT pe un vector de sample-uri ale fisierului
            audio, iar aceste date sunt date complexe

        - CArray Sampling(char* filename,int& sample)
            Functia primeste ca parametru numele unui fisier audio si adresa
            unei variabile in care va fi stocat numarul total de sample-uri
            din fisierul audio (cu cat acest numar este mai mare creste precizia
            analizei celor 2 fisier dar si timpul de executie)

        - double distance(Complex input,Complex compare)
            Functia primeste 2 parametrii ambii fiind sample-uri, unul este de la
            fisierul de input, altul este sample-ul fisierului cu, care se compara.
            Pentru a compara cele 2 valori , folosim formula pentru calculul distantei
            dintre 2 puncte in planul complex.
**/
//============================//
int main(int argc, char* argv[])
{
    if(argc == 1) return -1;
    /**
        Fisier pentru a transfera datele intre interfata si programul propriu-zis,
        acesta este sters dupa incheierea executiei programului
    **/
    ofstream file;
    file.open("output.txt");
    /**
        main-ul primeste 2 argumente, 2 path-uri catre fisierele audio, care mai apoi
        sunt trimise pentru a fi impartite in sample-uri, si se retin si in cate sample-uri
        s-au impartit pentru a putea face comparatia procentuala intre ele
    **/
    int sample1,sample2;
    CArray input = Sampling(argv[1],sample1);
    CArray compare = Sampling(argv[2],sample2);
    /**
        Se face calculul dintre cele 2 sample-uri si daca sunt similare, (din nou cu cat
        eroare e mai mica precizia este mai exacta) se adauga la un total pentru a obtine
        rezultatul procentual
    **/
    int maxsample = (sample1 > sample2) ? (sample2) : (sample1);
    double total = 0,tmp;
    for(int i=0;i<maxsample/100;i++)
    {
        tmp = distance(input[i],compare[i]);
        if(tmp < 0.0015) total++;
    }
    /**
        Se trimit datele catre interfata grafica pentru a fi interpretate si afisate, si apoi
        se incheie executia programului
    **/
    double result = ((100*total)/(maxsample/100));

    file << fixed << result;
    file.close();

	return 0;
}

CArray Sampling(char* filename, int& sample)
{
    /**
        Se incarca fisierul audio in memorie pentru a fi analizat, apoi se calculeaza cate
        sample-uri exista pe fiecare canal (in cazul nostru exista doar un canal)
    **/
    AudioFile<double> audiofile;
    Complex* timesamples;

    audiofile.load(string(filename));
    int channel = 0;
    int numSamples = sample = audiofile.getNumSamplesPerChannel();
    /**
        Se trece fiecare sample din fisierul audio in vector pentru a i se putea
        aplica algoritmul FFT
    **/
    timesamples = new Complex[numSamples/100];
    for(int i=0; i < numSamples/100;i++)
    {
        double currentSample = audiofile.samples[channel][i];
        timesamples[i] = currentSample;
        cout<< timesamples[i] << endl;
    }
    /**
        Calcularea in domeniul frecventa a sample-urilor si incheierea executiei
        subprogramului
    **/
    CArray data(timesamples,numSamples/100);
    fft(data);
    return data;
}
double distance(complex<double> input,complex<double> compare)
{
    return sqrt(
                (input.real()-compare.real())*(input.real()-compare.real()) +
                (input.imag()-compare.imag())*(input.imag()-compare.imag())
               );
}
void fft(std::valarray<complex_type> &x)
{
    /**
        Daca exista doar un element in vector nu se poate calcula FFT
    **/
    const size_t N = x.size();
    if (N <= 1) return;

    /**
        Am aplicat algoritmul Divide-et-Impera pentru a usura calculul
    **/
    std::valarray<complex_type> even = x[std::slice(0, N/2, 2)];
    std::valarray<complex_type> odd = x[std::slice(1, N/2, 2)];

    fft(even);
    fft(odd);

    /**
        Am trecut sample-urile din domeniul timp in frecventa pentru a putea
        fi comparate
    **/
    for (size_t k = 0; k < N/2; ++k)
    {
        complex_type t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
