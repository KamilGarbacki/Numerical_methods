#include <iostream>
#include <vector>

typedef std::vector<std::vector<double>> matrix;



void sum_matrix(matrix &A, std::vector<double> B, int n){
    for (int i = 0; i < n; ++i) {
        A[i].push_back(B[i]);
    }
}


void array_calc(int n, matrix &mat, int n1, int n2, double x){
    for (int i = 0; i < n + 1; i++){
        mat[n1][i] -= x*mat[n2][i];
    }

}

void swap(int n, matrix &mat, int n1, int n2){
    std::vector<double> temp;
    for (int i = 0; i < n+1; i++) {
        temp.push_back(mat[n1][i]);
        mat[n1][i] = mat[n2][i];
        mat[n2][i]=temp[i];
    }
}

void rearange(int n, matrix &mat){
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

std::vector<double> gauss_elimination(matrix &mat, std::vector<double> B, int n){
    sum_matrix(mat, B, n);
    rearange(n, mat);

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if(mat[j][i] != 0){
                array_calc(n, mat, j, i, mat[j][i]/mat[i][i]);
            }
        }
    }
    std::vector<double> results;
    for (int i = n-1; i >= 0; i--) {
        size_t k = results.size() - 1;
        double res = mat[i][n];

        for (int j = i+1; j < n; j++) {
            res -= mat[i][j] * results[k];
            k --;
        }

        res /= mat[i][i];

        results.push_back(res);
    }

    return results;
}


int main() {
//    matrix mat = {{1.f, -3.f, 4.f, 6.8f, 9.f, 74.64f},
//                  {-3.f, 2.f, 4.6f, 6.3f, -10.f, -40.26f},
//                  {2.f, -1.f, 2.8f, -8.4f, -5.f, -2.32f},
//                  {-6.f, 2.f, 7.f, -0.5f, -0.9f, 12.6f},
//                  {5.f, -2.f, -0.5, 12.f, -4.f, -8.9f}};

    matrix mat2 = {{1.f, -3.f, 4.f, 6.8f, 9.f},
                  {-3.f, 2.f, 4.6f, 6.3f, -10.f},
                  {2.f, -1.f, 2.8f, -8.4f, -5.f},
                  {-6.f, 2.f, 7.f, -0.5f, -0.9f},
                  {5.f, -2.f, -0.5, 12.f, -4.f}};

    std::vector<double> B = {74.64f, -40.26f, -2.32f, 12.6f, -8.9f};

//    for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 5; j++) {
//            std::cout << "|" << mat2[i][j] << "|";
//        }
//        std::cout << std::endl;
//    }
    std::vector<double> results = gauss_elimination(mat2, B, 5);
    std::cout << "---------" << std::endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << "|" << mat2[i][j] << "|";
        }
        std::cout << std::endl;
    }

    for (double result : results) {
        std::cout << "'" << result << "' ";
    }

    return 0;
}
