#include <iostream>
#include <cmath>
#include <vector>
#include <functional>

typedef std::vector<std::vector<double>> matrix;

std::vector<double> A = {0.236927f, 0.478629f, 0.568889f, 0.478629f, 0.236927f};
std::vector<double> X = {-0.906180f, -0.538469f, 0, 0.538469f, 0.906180f};

double calc_x1(double a, double b, int i, int N){
    return (a+(i*((b-a)/N)));
}

double calc_x2(double a, double b, int i, int N){
    return (a+((i+1)*((b-a)/N)));
}

double horner(std::vector<double> poly, double x)
{
    double result = poly[0];

    for (int i=1; i<poly.size(); i++)
        result = result*x + poly[i];

    return result;
}

double fsin(double x){
    return sin(x);
}

void sum_matrix(matrix &A, std::vector<double> B, int n){
    for (int i = 0; i < n; ++i) {
        A[i].push_back(B[i]);
    }
}

//subtracts contents of one row, multiplied by an x variable, from another row
void array_calc(int n, matrix &mat, int n1, int n2, double x){
    for (int i = 0; i < n + 1; i++){
        mat[n1][i] -= x*mat[n2][i];
    }

}

//swaps placement of two rows
void swap(int n, matrix &mat, int n1, int n2){
    std::vector<double> temp;
    for (int i = 0; i < n+1; i++) {
        temp.push_back(mat[n1][i]);
        mat[n1][i] = mat[n2][i];
        mat[n2][i]=temp[i];
    }
}

//rearrange rows placement to put the 0's in the optimal position
void rearrange(int n, matrix &mat){
    for (int i = 0; i < n; i++) {
        for (int j = n-1; j >= 0; j--) {
            if(mat[i][j] == 0){
                if(j == n-1){
                    swap(n, mat, i, 0);
                }else{
                    swap(n, mat, i, j+1);
                }
            }
        }
    }
}

double Gaussian_quadratures(double a, double b, int steps, std::function<double(double x)> F){
    double result = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j <= 5; j++) {
            double arg = (calc_x2(a, b, i, steps) - calc_x1(a, b, i, steps)) / 2.f;
            arg *= X[j];
            arg += (calc_x2(a, b, i, steps) + calc_x1(a, b, i, steps)) / 2;
            result += A[j] * F(arg)/*horner(poly1, arg) - horner(poly2, arg)*/;
        }
    }

    return result * (calc_x2(a, b, 1, steps) - calc_x1(a, b, 1, steps)) / 2;
}

std::vector<double> Gauss_elimination(matrix &mat, std::vector<double> B, int n){
    sum_matrix(mat, B, n);
    rearrange(n, mat);
    //transform matrix to upper triangular matrix
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if(mat[j][i] != 0){
                array_calc(n, mat, j, i, mat[j][i]/mat[i][i]);
            }
        }
    }
    //calculate the results
    std::vector<double> results;
    for (int i = n-1; i >= 0; i--) {
        size_t k = results.size() - 1;
        double res = mat[i][n];

        for (int j = i+1; j < n; j++) {
            res -= mat[i][j] * results[k];
            k --;
        }

        res /= mat[i][i];
        //results are reversed REMEMBER THAT
        results.push_back(res);
    }

    return results;
}

std::vector<double> aproximation(double a, double b, int size, std::function<double(double x)> F){
    matrix A;
    std::vector<double> B;
    for (int i = 0; i < size; i++) {
        std::vector<double> temp;
        for (int j = 0; j < size; j++) {
            temp.push_back(Gaussian_quadratures(a, b, 3, [&](double x){return pow(x, j+i);}));
        }
        A.push_back(temp);
        B.push_back(Gaussian_quadratures(a,b,4, [&](double x){return F(x)*pow(x,i);}));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout<<B[i] << std::endl;
    }

    return Gauss_elimination(A, B, size);
}

int main() {

    std::vector<double> results =  aproximation(0, M_PI/2, 3, fsin);
    std::cout << "----------------------------------------- " << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << results[i] << " ";
    }

    return 0;
}
