#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<double>> variables;

variables A = { {1, 1, 0, 0, 0},
                {5/9.f, 8/9.f, 5/9.f, 0, 0},
                {0.347855f, 0.652145f, 0.652145f, 0.347855f, 0},
                {0.236927f, 0.478629f, 0.568889f, 0.478629f, 0.236927f} };


variables X = {{-0.577350f, 0.577350f, 0, 0, 0},
               {-0.774597f, 0.f, 0.774597f, 0, 0},
               {-0.861136f, -0.339981f, 0.339981f, 0.861136f, 0},
               {-0.906180f, -0.538469f, 0, 0.538469f, 0.906180f}};

double F1(double x){
    return std::pow(x,2)*std::pow(sin(x),3);
}

double calc_x1(double a, double b, int i, int N){
    return (a+(i*((b-a)/N)));
}

double calc_x2(double a, double b, int i, int N){
    return (a+((i+1)*((b-a)/N)));
}

double horner(std::vector<double> poly, int n, double x)
{
    double result = poly[0];

    for (int i=1; i<n; i++)
        result = result*x + poly[i];

    return result;
}

std::vector<double> poly_multiply(std::vector<double> p1, std::vector<double> p2, int N1 ,int N2){
    std::vector<double> result;

    for (int i = 0; i < N1+N2-1; i++) {
        result.push_back(0);
    }

    for (int i =0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            result[i+j] += p1[i]*p2[j];
        }
    }
    return result;
}

double Gaussian_quadratures(double a, double b, int table_val, int steps, int deg, std::vector<double> poly1, std::vector<double> poly2){
    double result = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j <= table_val; j++) {
            double arg = (calc_x2(a, b, i, steps) - calc_x1(a, b, i, steps)) / 2.f;
            arg *= X[table_val - 1][j];
            arg += (calc_x2(a, b, i, steps) + calc_x1(a, b, i, steps)) / 2;
            result += A[table_val - 1][j] * horner(poly1, deg, arg) * horner(poly2, deg, arg);
        }
    }

    return result * (calc_x2(a, b, 1, steps) - calc_x1(a, b, 1, steps)) / 2;
}

int main() {
    std::vector<double> p1 = {1, 2, 1, -2};
    std::vector<double> p2 = {2, 1, -1, 10};

    int N = 4;

    std::cout << Gaussian_quadratures(-2.f, 2.f, 4, 10, N, p1, p2) << std::endl;

    return 0;
}
