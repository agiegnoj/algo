#include <vector>
#include <iostream>
#include <random>

using namespace std;

template <typename T>

class PolynomialRealRoots{

    public:
 
    T rootLaGuerre (const vector <T>& p, T epsilon){

        random_device rd;
        mt19937 gen(rd());
        const int depth = 100;
       
        T bound = cauchyBound(p);

        uniform_real_distribution<T> dis(-bound, bound);

        vector<T> guesses;

        int degree = p.size()-1;

        for (int i = 0; i < 10; i++){
            guesses.push_back(dis(gen));
        }

        vector<T> firstDer = derivative(p);
        vector<T> secDer = derivative(firstDer);

        for (T x : guesses){
            for (int i = 0; i < depth; i++){
                if (abs((evaluate(p, x)))<epsilon){
                    return x;
                }

                T eval = evaluate (p, x);

                T G = evaluate(firstDer, x)/eval;
                T H = G*G - (evaluate(secDer, x))/eval;

                T radicand = (degree-1)*(degree*H-G*G);

                if (radicand < 0) break;

                T d = max (abs(G+sqrt(radicand)), abs(G-sqrt(radicand)));

                if (abs(d) > epsilon){
                    T a = degree / d;
                    x = x-a;
                }else{
                    break;
                }
            } 
        }
        return numeric_limits<T>::quiet_NaN(); 
    }

    T rootNewton(const vector<T>& p, T epsilon){
        const int depth = 100;
        vector<T> guesses;

        vector<T> der = derivative(p);

        int degree = p.size()-1;

        T guess = null;

        for (int i = 0; i < 3; i++){
            T guess = rootLaGuerre(p);
            if (!isnan(guess))
            guesses.push_back(guess);
        }

        for (T x : guesses){
            for (int i = 0; i< depth; i++){
                if (abs(evaluate(p, x)) < epsilon)
                return x;

            T den = evaluate(der, x);
            if (den != 0){
                x = x - evaluate(p, x)/ den;
            }else{
                break;
            } 
            }
        }
        return numeric_limits<T>::quiet_NaN();   
    }


    T evaluate(const vector<T>& coeff, T x){ 
        T res = 0;

        for (int i = coeff.size()-1; i >= 0; i--){
            res = coeff[i]+res*x;
        }

        return res;
    }


    void reduce(vector<T>& p, T r) {     
       for (int i = p.size() - 2; i >= 0; i--) {
        p[i] += p[i + 1] * r;
     }
       if (!p.empty()){
        p.erase(p.begin());
     }
     }

  
    vector<T> derivative(const vector<T>& coeff){

        vector<T> d = coeff;
          
        for (int i = 1; i < d.size(); i++){
            d[i] *= i;
        }

        if (!d.empty())
        d.erase(d.begin());

        return d;
    }

    T cauchyBound(const vector<T>& p){
        T cauchyBound = 0;
        T den = abs(p[p.size()-1]) != 0 ? abs(p[p.size()-1]) : 1;

        for (T coeff : p){
            cauchyBound = max(cauchyBound, 1+ abs(coeff/den));
        }

        return cauchyBound;
    }
    };
    
