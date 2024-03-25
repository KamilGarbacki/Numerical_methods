#include <iostream>

struct point{
    double x;
    double y;
};

double Lagrange_Interpolation(point p[], int size, double x){
    double result = 0;
    for (int i = 0; i < size; i++) {
        double temp = p[i].y;
        for (int j = 0; j < size; j++) {
            if(p[j].x != p[i].x)
                temp *= (x - p[j].x)/(p[i].x - p[j].x);
        }
        result += temp;
    }
    return result;
}

int main() {

    point points[] = {{-2.f,5.f}, {-1.f, -2.f}, {0.f, 4.f}, {1.f, -7.f}, {2.f, 2.f}};
    for (double i = -2.f; i <= 2.f ; i+=0.01f){
        std:: cout  << Lagrange_Interpolation(points, 5, i) << std::endl;
    }
    return 0;
}
