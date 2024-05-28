#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<std::vector<double>> variables;

variables A = { {1, 1, 0, 0, 0},
                {5/9.f, 8/9.f, 5/9.f, 0, 0},
                {0.347855f, 0.652145f, 0.652145f, 0.347855f, 0},
                {0.236927f, 0.478629f, 0.568889f, 0.478629f, 0.236927f} };


variables X = {{-0.577350f, 0.577350f, 0, 0, 0},
               {-0.774597f, 0.f, 0.774597f, 0, 0},
               {-0.861136f, -0.339981f, 0.339981f, 0.861136f, 0},
               {-0.906180f, -0.538469f, 0, 0.538469f, 0.906180f}};

variables F = {
        {1.f, 0.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 0.f, 1.f}
};

variables G = {
        {0.f, 0.f, 0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f, 0.f, 0.f},
        {0.f, 0.f, 0.f, 0.f, 0.f}
};

double calc_x1(double a, double b, int i, int N){
    return (a+(i*((b-a)/N)));
}

double calc_x2(double a, double b, int i, int N){
    return (a+((i+1)*((b-a)/N)));
}

double horner(std::vector<double> poly, int n, double x){
    double result = poly[n];
    while(n-->0){
        result = poly[n] +x*result;
    }
    return result;
}

double calc_func(double x){
    double result = sin(x*(-1.f));
    result += exp(x*(-1.f));
    result-= pow(x,3);
    return result;
}

double Gauss(double a, double b, int steps, std::vector<double> poly1, std::vector<double> poly2){
    double result = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j <= 4; j++) {
            double arg = (calc_x2(a, b, i, steps) - calc_x1(a, b, i, steps)) / 2.f;
            arg *= X[3][j];
            arg += (calc_x2(a, b, i, steps) + calc_x1(a, b, i, steps)) / 2;
            result += A[3][j] * horner(poly1, poly1.size(), arg) * horner(poly2, poly2.size(), arg);

        }
    }
    return (result * ((b-a)/steps)) / 2;
}

double Gauss(double a, double b, int steps, std::vector<double> poly){
    double result = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j <= 4; j++) {
            double arg = (calc_x2(a, b, i, steps) - calc_x1(a, b, i, steps)) / 2.f;
            arg *= X[3][j];
            arg += (calc_x2(a, b, i, steps) + calc_x1(a, b, i, steps)) / 2;
            result += A[3][j] * calc_func(arg) * horner(poly, poly.size(), arg);
        }
    }
    return (result * ((b-a)/steps)) / 2;
}

void Orto(double a, double b, int n){
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++)
            G[i][k] = F[i][k];
        for (int j = 0; j < i; j++) {
            double ratio = Gauss(a, b, n, F[i], G[j]) / Gauss(a, b, n, G[j], G[j]);

            for (int k = 0; k < 5; ++k) {
                G[i][k] -= ratio * G[j][k];
            }
        }
    }
}

variables calcP(){
    variables P = G;
    for (int i = 0; i < P.size(); ++i) {
        double temp = 1 / sqrt(Gauss(0, 1, 100, P[i], P[i]));
        for (int j = 0; j < P.size(); ++j) {
            P[i][j] *= temp;
        }
    }
    return P;
}

std::vector<double> aproximation(){
    std::vector<double> alfa;
    variables P = calcP();
    for (const auto & i : P) {
        alfa.push_back(Gauss(0,1,100, i));
    }

    for (double i : alfa) {
        std::cout<<i << std::endl;
    }
    std::vector<double> W;
    for (int i = 0; i < P.size(); ++i) {
        W.push_back(0);
        for (int j = 0; j < P.size(); ++j) {
            W[i]+=alfa[j]*P[j][i];
        }
    }
    return W;
}


int main() {

    Orto(0, 1, 10000);
    std::vector<double> W = aproximation();

    for (double i : W) {
        std::cout<<i<<std::endl;
    }

    return 0;
}
