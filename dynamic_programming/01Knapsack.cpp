#include <vector>
using namespace std;
template<typename T>

class ZeroOneKnapsack{
    public: 
    vector<T> ItemValueList(const vector <T> value, const vector<T> weight, T capacity){
        if (value.size()!= weight.size()) return {};

        T n = value.size();

        vector<vector<T>> tabulation (n+1, vector<T> (capacity+1, 0));
        vector<T> res;

        for (T i = 1; i <= n; i++){
            for (T j = 0; j <= capacity; j++){
                if (weight [i-1]  <= j) 
                tabulation[i][j] = max(value[i-1]+tabulation[i-1][j-weight[i-1]], tabulation[i-1][j] );
                else
                tabulation [i][j] = tabulation[i-1][j];

            }
        }

        T w = capacity;

        for (T i = n; i > 0; i--){
            if (tabulation[i][w] != tabulation[i-1][w]){
                res.push_back(value[i-1]);
                w -= weight[i-1];
            }  
        }

        return res;
        }

        T MaxValue(vector<T>& value, vector<T>& weight, T capacity  ){

            if (value.size() != weight.size())
            return -1;

            T n = value.size();

            vector <T> tabulation (capacity+1, 0);

            for (T i = 0; i < n; i++){
            for (T j = capacity; j >= weight[i]; j--){
                tabulation [j] = max (tabulation[j], tabulation[j-weight[i]] + value[i]);

            }
     
        }

        return tabulation[capacity];

        }

};