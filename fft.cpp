#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

/****************************************************************************
 *
 *  Fast Fourier transform
 *
 *  Cooley–Tukey algorithm
 *
 *  Arguments: input complex vector, output complex vector
 *
 *  Input vector size must be a power of 2
 *
 ***************************************************************************/
complex <float> TwiddleFactor(int k, int N)
{
    return complex <float> (cos(-2*M_PI*k/N) , sin(-2*M_PI*k/N));
}

void FFT(vector <complex <float> > &input, vector <complex <float> > &output)
{
    int n = input.size();
    if (n == 2)
    {
        output[0] = input[0] + input[1];
        output[1] = input[0] - input[1];
    }
    else
    {
        vector <complex <float> > even (n/2);
        vector <complex <float> > odd (n/2);
        for (int i = 0; i < n/2; i++)
        {
            even[i] = input[2 * i];
            odd[i]  = input[2 * i + 1];
        }
        vector <complex <float> > outEven (n/2);
        vector <complex <float> > outOdd (n/2);

        FFT(even, outEven);
        FFT(odd, outOdd);

        for (int i = 0; i < n/2; i++)
        {
            output[i] 		= outEven[i] + TwiddleFactor(i, n) * outOdd[i];
            output[i + n/2] = outEven[i] - TwiddleFactor(i, n) * outOdd[i];
        }
    }
}
/***************************************************************************/

int main()
{
    int N = 256; // Vector size must be a power of 2
    vector <complex<float> > x (N);
    vector <complex<float> > X (N);

    // Test input
    for(int i = 0; i < N; i++){
        x[i] = 10 + 100*sin(10*2*M_PI*i/N);
    }

    // Calculation
    FFT(x, X);

    // Test output
    for(int i = 0; i < N; i++){
        cout << i << ' ' << abs(X[i])*2/N << '\n';
    }
    return 0;
}
