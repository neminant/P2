#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N)
{
    int n = 0;
    float suma = 0;
    for (n = 0; n < N - 1; n++)
    {
        suma = suma + (x[n]) * (x[n]);
    }
    return (10 * (log10(suma / N)));
}

float compute_am(const float *x, unsigned int N)
{
    int n;
    float suma = 0;
    for (n = 0; n < N - 1; n++)
    {
        suma = suma + fabs(x[n]);
    }
    return (suma / N);
}

float compute_zcr(const float *x, unsigned int N, float fm)
{
    int n;
    float cont = 0;
    for (n = 1; n < N - 1; n++)
    {
        if (x[n] * x[n - 1] <= 0)
        { //cuando la multiplicación da negativa son de signo contrario.
            cont++;
        }
    }

    return (fm * cont) / (2 * (N - 1));
}

float compute_power_hamming(const float *x, float fm)
{
    float Tdesp = 0.010;
    float Tlong = 0.020;
    float a = 0.53836, b = 0.46164, pi = 3.1415926535,w1 =0, f1=0;
    int N = fm * Tlong, M = Tdesp * fm;
    float w[N], v[N], f[N], p[N]; /* w[N] =  Ventana de hamming al cuadrado ; v[N] = Ventana de hamming ; 
    f[N] = (Xi[n]*v[n])^2; p[N] funcion resultante */
    int i, n;
    for (i = 0; i < M; i++)
    {

        for (n = 0; n < N - 1; n++)
        {
            float coseno = cos(2 * pi * n / (N-1));
            v[n] = (a - b * coseno);
            w[n] = v[n] * v[n]; /* Ventana de hamming al cuadrado */
            f[n] = x[i * M + n]  * x[i * M + n] * w[n];
        }
        for (n = 0; n < N - 1; n++)
        {
            
            w1 = w1 + w[n];
            f1 = f1 + f[n];
        }


        p[i] = 10 * log10(f1 /w1 );
    }

    return *p;
}