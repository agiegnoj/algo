#include <vector>
#include <stack>
#include <unordered_set>
#include <iostream>
using namespace std;


class EulerianCircuit{
    public:
    
    vector <int> eulerianCircuit(vector<vector<int>>& graphAdjList, bool undirected){
        stack<int> currentPath;
        vector<int> eulerianCircuit;
        currentPath.push(0);
        vector<unordered_set<int>> usedEdges(graphAdjList.size());
        
        while (!currentPath.empty()){
            int currentNode = currentPath.top();
            bool found = false;
            while (!graphAdjList[currentNode].empty()){
                int nextNode = graphAdjList[currentNode].back();
                graphAdjList[currentNode].pop_back();
                if (undirected && !usedEdges[nextNode].count(currentNode)){
                    currentPath.push(nextNode);
                    usedEdges[nextNode].insert(currentNode);
                    usedEdges[currentNode].insert(nextNode);
                    found = true;
                    break;
                }else if (!undirected){
                    currentPath.push(nextNode);
                    found = true;
                    break;
                }
            }
            if (!found){
                eulerianCircuit.push_back(currentNode);
                currentPath.pop();
            }
        }
        
        for (vector<int> n : graphAdjList){
            if (!n.empty())return {};
        }
        
        if (eulerianCircuit[0] != eulerianCircuit[eulerianCircuit.size()-1])return {};
        return eulerianCircuit;
        
    }
};