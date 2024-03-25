#include <iostream>

double horner(double fac[], int deg, int arg){
    double result = fac[deg];
    while(deg-- > 0)
        result = fac[deg] + arg*result;
    return result;
}

double horner_newton(double b[], double x[], int deg, int arg){
    double result = b[deg];
    while(deg-- > 0)
        result = b[deg] + (arg - x[deg])*result;
    return result;
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

    std::cout << "wartosc wielomianu dla -4: " << horner(fac, degree, arg1) << std::endl;
    std::cout << "wartosc wielomianu dla -1: " << horner(fac, degree, arg2) << std::endl;

    std::cout << "newton wartosc wielomianu dla 0: " << horner_newton(b, x, degree, arg3) << std::endl;
    std::cout << "newton wartosc wielomianu dla 2: " << horner_newton(b, x, degree, arg4) << std::endl;

    return 0;
}
