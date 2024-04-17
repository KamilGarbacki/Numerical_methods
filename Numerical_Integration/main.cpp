#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

double calc_poly(int N, double x, std::vector<double> poly){
    double result = 0.f;
    for(double i : poly){
        result += i*pow(x, N);
        N--;
    }
    return result;
}

std::vector<double> get_range(double a, double b, int n){
    double dif = b - a;
    dif = dif / n;
    std::vector<double> range;
    for (int i = 0; i <= n; i++) {
        range.push_back(a);
        a+=dif;
    }
    return range;
}

double F1(double x){
    return std::pow(x,2)*std::pow(sin(x),3);
}

double F2(double x){
    return (x-1)*exp(pow(x,2));
}

double F3(double x){
    if(x==0){
        return 1;
    }
    return sin(x)/x;
}

double F4(double x){
    if(x==0){
        return 0;
    }
    return sin(1/x);
}



double integration_Cotesa(int n, double a, double b, std::function<double(double x)> calc, std::vector<double> &quads){
    std::vector<double> x = get_range(a, b, n);
    double result = 0;
    for (int i = 1; i <= n; i++) {
        result += (x[i] - x[i-1]) * (calc(x[i-1]) + calc(x[i]));
        quads.push_back(result);
    }
    result *= 0.5f;
    return result;
}

double integration_Simsona(int n, double a, double b, std::function<double(double x)> calc, std::vector<double> &quads){
    std::vector<double> x = get_range(a, b, n);
    double temp0=0, temp1=0, temp2=0, temp3=0;
    double h = (b-a)/n;
    temp0 = calc(x[0]);
    temp3 = calc(x[n-1]);
    for (int i = 1; i <= n; i+=2) {
        temp1 += calc(x[i]);
        quads.push_back(temp0 + 4*temp1 + 2*temp2 + temp3);
    }
    for (int i = 2; i <= n; i+=2) {
        temp2 += calc(x[i]);
        quads.push_back(temp0 + 4*temp1 + 2*temp2 + temp3);
    }
    double result = temp0 + 4*temp1 + 2*temp2 + temp3;
    result *= (1.f/3)*h;
    return result;
}

void display_table(double a, double b, int n, std::function<double(double x)> calc){
    std::vector<double> h = get_range(a,b,n);
    std::vector<double> quads_Simson;
    std::vector<double> quads_Cotesa;
    double res_sim = integration_Simsona(n, a, b, calc, quads_Simson);
    double res_cot = integration_Cotesa(n, a, b, calc,quads_Cotesa);
    for (int i = 0; i < n; i++) {
        std::cout<<"h: " << h[i] << " Simson: " << quads_Simson[i] << " Cotes: " << quads_Cotesa[i] <<std::endl;
    }
    std::cout<<"---------------------"<<std::endl;
    std::cout<<"Final results: "<<std::endl;
    std::cout<<"Simson: " << res_sim << " Cotes: " << res_cot << std::endl;
}

int main() {
    int n = 1000; // range

    std::cout<<"Dla F1: "<<std::endl;
    display_table(0, 4.5, n, F1);
    std::cout<<"Dla F2: "<<std::endl;
    display_table(-2, 2, n, F2);
    std::cout<<"Dla F3: "<<std::endl;
    display_table(0, 1, n, F3);
    std::cout<<"Dla F4: "<<std::endl;
    display_table(0.0001, 1, n, F4);

    return 0;
}
