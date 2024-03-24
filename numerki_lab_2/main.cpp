#include <iostream>

struct point{
    double x;
    double y;
};


double Lagrange(point data[], int n, double x){
    double result = 0;
    for (int i = 0; i < n; i++) {
        double temp = data[i].y;
        for (int j = 0; j < n; j++) {
            if(data[j].x != data[i].x)
                temp *= (x - data[j].x)/(data[i].x - data[j].x);
        }
        result += temp;
    }
    return result;
}


int main() {

    //point points[] = {(-2.f,5.f), (-1.f, -2.f), (0.f, 4.f), (1.f, -7.f), (2.f, 2.f)};
    point points[] = {{-2.f,5.f}, {-1.f, -2.f}, {0.f, 4.f}, {1.f, -7.f}, {2.f, 2.f}};
    for (double i = -2.f; i <= 2.f ; i+=0.01f){
        std:: cout  << Lagrange(points, 5, i) << std::endl;
    }
    return 0;
}
