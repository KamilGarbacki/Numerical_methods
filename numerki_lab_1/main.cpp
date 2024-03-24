#include <iostream>


double horner_nat(double fac[], int deg, int arg){
    if(deg == 0)
        return fac[0];
    return arg * horner_nat(fac, deg - 1, arg) + fac[deg];
}


int horner(double fac[], int degree, double x)
{
    double res = fac[degree];

    for(int i = degree-1; i >= 0; i--){
        res = res*x + fac[i];
        std::cout << i << " "  << res << std::endl;
    }
    return res;
}

int horner2_newton(double b[], double x[], int degree, double arg)
{
    double res = b[degree];
    for(int i = degree-1; i>=0; i--){
        res = b[degree] + (arg - x[degree]) * res;
    }
    return res;
}

double* zmiana(double b[], double x[], int degree){
    double* a = new double[degree];
    a[degree-1]  = b[degree-1];
    for(int i = degree - 2; i >= 0; i--){
        a[i] = b[i];
        for(int j = i; j< degree-1; j++){
            a[j] -= x[i] * a[j+1];
        }
    }
    return a;
}

double* NewtonToNatural(double* const b, double* const x, unsigned int n){
    double* a = new double[n + 1];
    a[n] = b[n]; // a_n = b_n
    for (int i = n - 1; i >= 0; i--)
    {
        a[i] = b[i]; // max value of a_i
        for (int j = i; j < n; j++)
            a[j] -= x[i] * a[j + 1];
    }
    return a;
}

int main() {
    int degree = 3;

    int arg1 = -4;
    int arg2 = -1;
    int arg3 = 0;
    int arg4 = 2;

    double fac[4] = {-2.f, -13/6.f, 4/3.f, 0.5};
    double b[4] = {0.5, 7/6.f, 5/3.f, -4.f};
    double x[3] = {0, 1, 4};

    double wynik =  horner(fac, degree, arg1);
    std::cout << "wartosc wielomianu dla -4: " << wynik << std::endl;

//    std::cout << "wartosc wielomianu dla -1: " << horner(fac, degree, arg2) << std::endl;
//
//    std::cout << "newton wartosc wielomianu dla 0: " << horner2_newton(b, x, degree, arg3) << std::endl;
//    std::cout << "newton wartosc wielomianu dla 2: " << horner2_newton(b, x, degree, arg4) << std::endl;
    std::cout << "-----------------" << std::endl;
    double * a = NewtonToNatural(b,x,degree);
    for (int i = 0; i < degree; i++) {
        std::cout << a[i] << std::endl;
    }
    return 0;
}
