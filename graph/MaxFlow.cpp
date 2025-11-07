#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;


class MaxFlow{
    public:
    int maxFlow (vector<vector<int>>&graph, int source, int sink){
        bool canAugment = true;
        int maxFlow = 0;
        
        while (canAugment){
            vector<int> path;
            int flow = 1e9;
            bfs(graph, source, sink, path, flow);
            if (!path.empty()){
                maxFlow += flow;
                for (int i = path.size()-1; i > 0; i--){
                    graph[path[i-1]][path[i]] -= flow;
                    graph[path[i]][path[i-1]] += flow;
                }
            }else{
                canAugment = false;
            }
        }
        
        return maxFlow;
        
    }
    
    private:
    
    void bfs(vector<vector<int>>&graph, int source, int sink, vector<int>& path, int& flow){
        vector <int> prev (graph.size(), -1);
        vector<bool> visited (graph.size());
        queue<int> q;
        q.push(source);
        bool pathFound = false;
        
        visited[source] = true;
        
        
        while (!q.empty() && !pathFound){
            int current = q.front();
            q.pop();
            
            for (int n = 0; n < graph.size(); n++){
                if (graph[current][n] > 0 && !visited[n]){
                    prev [n] = current;
                    q.push(n);
                    visited[n] = true;
                    if (n == sink){
                        pathFound = true;
                        break;
                    }
                }
            }
        }
        
        if (pathFound){
                int current = sink;
                while (prev[current] != -1){
                    path.push_back(current);
                    int previous = prev[current];
                    flow = min (flow, graph[previous][current]);
                    current = previous;
                }
                
                reverse(path.begin(), path.end());
                
        }else{
            path.clear();
        }
        
    }
};