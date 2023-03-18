#include <math.h>
#include "pav_analysis.h"


float hamming_window(int n, int m){
    return (float) 0.54 -0.46*cos((2*M_PI*n)/(m-1));
}
float compute_power(const float *x, unsigned int N) {
    float pot= 1e-12;// 1e-12 evita infinits
    for(unsigned int i=0; i<N; i++)
    {
        pot+= x[i]*x[i];
    }
    return (10*log10(pot/N)); //retorna en decibels
}

float compute_am(const float *x, unsigned int N) {
    int i;
    float sum=0;
    float res=0;
    for (i=0; i<N-1; i++){
        sum=fabs(sum+x[i]);
    }
    res=sum/N;
    return res;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    int contador = 0;
    float zcr = 0;
    for (unsigned int n = 1 ; n < N ; n++){
        if ((x[n] * x[n-1]) < 0){ 
            contador++;
        }
    }
    zcr = fm/(2.0*(N-1.0))*contador;

    return zcr;
}
