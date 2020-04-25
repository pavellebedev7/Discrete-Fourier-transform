#include <iostream>
#include <cmath>

using namespace std;

/****************************************************************************
 *
 *  Discrete Fourier transform
 *
 *  Arguments: input array, output array, input size
 *
 ***************************************************************************/
void FT (float *input, float **output, int size)
{
    // Memory Allocation
    float angle;
    float *reSum = new float[size];
    float *imSum = new float[size];

    // Frequency Cycle
    for (int k = 0; k < size/2; k++)
    {
        reSum[k] = 0.;
        imSum[k] = 0.;
        // Point Cycle
        for (int n = 0; n < size; n++)
        {
            angle    = (-2.*M_PI*k*n/size);
            reSum[k] = (reSum[k] + input[n] * cos(angle));
            imSum[k] = (imSum[k] + input[n] * sin(angle));
        }
        output[0][k] = reSum[k]*2/size;
        output[1][k] = imSum[k]*2/size;
    }

    // Memory Deallocation
    delete[] reSum;
    delete[] imSum;
}

//Complex Numbers
// Absolute value
float abs0(float re, float im)
{
    return pow(re*re + im*im, .5);
}
// Phase
float phase(float re, float im)
{
    return atan2(im, re)*180./M_PI;
}
/***************************************************************************/

int main()
{
    // Test input
    int N = 200;
    float x[N];
    for(int i = 0; i < N; i++){
        x[i] = 10 + 100*sin(50*2*M_PI*i/N);
    }

    // Memory Allocation
    float** X = new float*[2];
    X[0] = new float[N/2];
    X[1] = new float[N/2];

    // Calculation
    FT(x, X, N);

    // Test output
    for(int i = 0; i < N/2; i++){
        if(abs0(X[0][i], X[1][i])<0.001){
            X[0][i] = 0;
            X[1][i] = 0;
        }
        cout << i << ' ' << abs0(X[0][i], X[1][i]) << '\n';
    }

    // Memory Deallocation
    delete[] X[0];
    delete[] X[1];
    delete[] X;
    return 0;
}
