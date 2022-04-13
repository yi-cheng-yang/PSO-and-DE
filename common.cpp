#ifndef COMMON
    #define COMMON
    
    #include <vector>
    #include <random>
    #include <cfloat>
    #include <fstream>
    #include <iostream>
    #include <string>
    using namespace std;

    using d1d = vector<double>;
    using d2d = vector<d1d>;
    using i1d = vector<int>;
    using i2d = vector<i1d>;

    random_device rd;
    mt19937_64 generator(rd());

    inline double Rdouble(double a, double b){
        uniform_real_distribution<double> d(a, b);
        return d(generator);
    }
    inline int Rint(int a, int b){
        uniform_int_distribution<int> i(a, b);
        return i(generator);
    }

    inline double cauchy_g(double mu, double gamma)
    {
        return mu + gamma * tan(M_PI * (Rdouble(0.0, 1.0) - 0.5));
    }

    inline double rand_normal(double mu, double sigma)
    {
        return mu + sigma * sqrt(-2.0 * log(Rdouble(0.0, 1.0))) * sin(2.0 * M_PI * Rdouble(0.0, 1.0));
    }
#endif

