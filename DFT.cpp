#include <math.h>
#include <complex>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

vector<complex<double>> dft(vector<complex<double>> X)
{
    int N = 1000;
    int K = N;

    complex<double> intSum;

    vector<complex<double>> output;
    output.reserve(K);

    for (int k=0; k<K; k++)
    {
        intSum = complex<double>(0,0);
        for (int n=0; n<N; n++)
        {
            double realPart = cos(((2*M_PI)/N)*k*n);
            double imagPart = sin(((2*M_PI)/N)*k*n);
            complex<double> w (realPart, -imagPart);
            intSum += X[n] * w;
        }
        output.push_back(intSum);
    }
    return output;
}

int main()
{
    int i = 0;
    while(i<500){
    int N = 1000;
    vector<complex<double>> signal;
    signal.reserve(N);

    double sigK = 3.0;
    double sigPhase = 0.0;

    for (int x=0; x<N; ++x)
    {
        auto currentSample = complex<double>
                (cos((2*M_PI/static_cast<double>(N))* sigK*static_cast<double>(x) + sigPhase), 0.0);

        signal.push_back(currentSample);
    }
    auto start = steady_clock::now();
    vector<complex<double>> Fx = dft(signal);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout<<duration.count()<<endl;
    cout<<"real\t "<<setw(12)<<"Imag"<<endl;
    for (int i=0; i<6; ++i)
    {
        cout <<i<<"\t" << Fx[i].real() / static_cast<double>(N)<<"\t"<<Fx[i].imag()/static_cast<double>(N)<<endl;
    }

    fstream f1;
    ofstream f1out;
    ifstream f1in;
    f1in.open("C++_DEBUG_FFT_TIME.txt");
    f1out.open("C++_DEBUG_FFT_TIME.txt", ios::app);
    if(f1in.is_open())
      f1out<<duration.count() <<"\n";

      f1in.close();
      f1out.close();

      i++;
      }
}