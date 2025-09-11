#include <vector>
#include <math.h>
using namespace std;
template <typename T>

class LinearDiophantine{

    public:

    vector<pair<T, T>> solveLinearDiophantineEquation(T a, T b, T c, T minX, T maxX, T minY, T maxY){
        T x; T y;
        T gcd = extendedGCD(a, b, x, y);
        vector<pair<T, T>> solutions;

        if (c % gcd == 0){
            x *= c/gcd;
            y *= c/gcd;
  
            T xStep = b/gcd;
            T yStep = a/gcd;

            T kMin = ceil((minX - x) / (double)xStep);
            T kMax = floor((maxX - x) / (double)xStep);
            T kMinY = ceil((y - maxY) / (double)yStep);
            T kMaxY = floor((y - minY) / (double)yStep);
            kMin = max(kMin, kMinY);
            kMax = min(kMax, kMaxY);

            for (T k = kMin; k<= kMax; k++){
                T newX = x + k*xStep;
                T newY = y-k*yStep;
                solutions.push_back({newX, newY});
            }

        }
        return solutions;    
    }

    T extendedGCD(T a, T b, T& x, T& y){
 
        T r0 = a; T r1 = b;
        T x0 = 1; T x1 = 0;
        T y0 = 0; T y1 = 1;

        while (r0 % r1 != 0){
            T rn = r0%r1;
            T q = r0/r1;
            T xn = x0-q*x1;
            T yn = y0 - q*y1;

            r0 = r1;
            r1 = rn;
            x0 = x1;
            x1 = xn;
            y0 = y1;
            y1 = yn;
        }
        x = x1;
        y = y1;
        return r1;

    }
};

