#include "Graph.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;


Graph::Graph(const char* const & edgelist_csv_fn) {
    ifstream file(edgelist_csv_fn);
    string line;
    int i = 0;
    while(getline(file, line)){
        istringstream ss(line);
        string from, to, weight;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, weight, '\n');
        edgelist.push_back(make_tuple(from,to,stod(weight)));
        unordered_map<int,double> empty;
        if(index.find(from) == index.end()){
            index[from] = i++;
            adjlist.push_back(empty); 
            nodelist.push_back(from);
        }
        if(index.find(to) == index.end()){
            index[to] = i++;
            adjlist.push_back(empty);
            nodelist.push_back(to);
        }
        adjlist[index[from]][index[to]] = stod(weight);
        adjlist[index[to]][index[from]] = stod(weight);

    }
    file.close();
}

Graph::~Graph(){
    nodelist.clear();
    index.clear();
    for(auto map: adjlist){
        map.clear();
    }
    adjlist.clear();
    edgelist.clear();
}

unsigned int Graph::num_nodes() {
    return index.size();
}

vector<string> Graph::nodes() {
    return nodelist;
}

unsigned int Graph::num_edges() {
    return edgelist.size();
}

unsigned int Graph::num_neighbors(string const & node_label) {
    return adjlist[index[node_label]].size();
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    unordered_map<int, double> neighbors= adjlist[index[u_label]];
    if(neighbors.find(index[v_label]) == neighbors.end()){
        return -1;
    }
    return adjlist[index[u_label]][index[v_label]];
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> v;
    for(auto edge : edgelist){
        if(get<0>(edge).compare(node_label) == 0){
            v.push_back(get<1>(edge));
        }
        if(get<1>(edge).compare(node_label) == 0){
            v.push_back(get<0>(edge));
        }
    }
    return v;
}
vector<string> reverse(vector<string> v){
    vector<string> w;
    for(int i = 0; i<(int)v.size();++i){
        w.push_back(v[v.size()-i-1]);
    }
    return w;
}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    queue<int> q;
    vector<string> v;
    unordered_map<int,int> pre;
    if(start_label.compare(end_label)==0){
        v.push_back(start_label);
        return v;
    }
    for(int i = 0; i<(int)nodelist.size();i++){
        pre[i] = -1;
    }
    unordered_set<int> visited;
    visited.insert(index[start_label]);
    q.push(index[start_label]);
    while(q.size()!= 0){
        int current = q.front();
        q.pop();
        for(auto kv: adjlist[current]){
            if(visited.find(kv.first)==visited.end()){
                int j = kv.first;
                q.push(j);
                visited.insert(j);
                pre[j] = current;
                if(j == index[end_label]){
                    while(j!=-1){
                        v.push_back(nodelist[j]);
                        j = pre[j];
                    }
                    return reverse(v);
                }
            }
        }
    }
    return v;


}

vector<tuple<string,string,double>> reverse(vector<tuple<string,string,double>> v){
    vector<tuple<string,string,double>> w;
    for(int i = 0; i<(int)v.size();++i){
        w.push_back(v[v.size()-i-1]);
    }
    return w;
}

vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    vector<tuple<string,string,double>> v;
    if(start_label.compare(end_label) == 0){
        v.push_back(make_tuple(start_label,end_label,-1));
        return v;
    }
    auto compare = [](pair<int, double> a,pair<int, double> b )->bool{
        if(a.second!= b.second){
            return a.second >b.second;
        }
        return a.first > b.first;
    };
    priority_queue<pair<int, double>, vector<pair<int,double>>, decltype(compare)> pq(compare);
    vector<pair<int,double>> pre;
    for(int i = 0; i<(int)nodelist.size();i++){
        pre.push_back(make_pair(-1,-1));
    }
    unordered_set<int> visited;
    pq.push(make_pair(index[start_label],0));
    while(pq.size()!=0){
        pair<int,double> p = pq.top();
        pq.pop();
        visited.insert(p.first);
        for(auto kv : adjlist[p.first]){
            if(visited.find(kv.first)==visited.end()){
                double distance = p.second + kv.second;
                if(distance < pre[kv.first].second  || pre[kv.first].second == -1){
                    pre[kv.first] = make_pair(p.first, distance);
                    pq.push(make_pair(kv.first,distance));
                }
            }

        }
    }
    int k = index[end_label];
    double d = pre[k].second;
    while(d!=-1){
        int previous = pre[k].first;
        double length = adjlist[k][previous];
        v.push_back(make_tuple(nodelist[previous],nodelist[k],length));
        k = previous;
        d = pre[k].second;
    }
    return reverse(v);
    
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    vector<vector<string>> v;
    unordered_set<int> visited;
    for(int i=0; i<(int)index.size(); ++i){
        if(visited.find(i) == visited.end()){
            queue<int> q;
            vector<string> components;
            components.push_back(nodelist[i]);
            q.push(i);
            visited.insert(i);
            while(q.size()!=0){
                int j = q.front();
                q.pop();
                for(auto kv:adjlist[j]){
                    if(visited.find(kv.first)==visited.end()){
                        if(kv.second <= threshold){
                            q.push(kv.first);
                            components.push_back(nodelist[kv.first]);
                            visited.insert(kv.first);
                        }
                    }
                }
            }
            v.push_back(components);
        }
    }
    return v;
}
DisjointSet::DisjointSet(int num){
    for(int i =0; i< num; i++){
        set.push_back(-1);
    }
    
}

DisjointSet::~DisjointSet(){
    set.clear();
}

int DisjointSet::find(int a){
    vector<int> compression;
    int curr = a;
    while(set[curr]!=-1){
        compression.push_back(curr);
        curr = set[curr];
    }
    for(int i: compression){
        set[i] = curr;
    }
    return curr;
}

void DisjointSet::u(int a, int b){
    if(find(a)!= find(b)){
        set[find(a)] = find(b);
    }
}

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    if(start_label.compare(end_label)==0){
        return 0;
    }
    int start = index[start_label];
    int end = index[end_label];
    DisjointSet s((int)index.size());
    sort(edgelist.begin(),edgelist.end(), [](tuple<string,string,double> a, 
        tuple<string,string,double> b)->bool{
            return get<2>(a) < get<2>(b);
        });
    for(auto e: edgelist){
        int a = index[get<0>(e)]; 
        int b = index[get<1>(e)]; 
        s.u(a,b);
        if(s.find(start) == s.find(end)){
            return get<2>(e);
        }
    }
    return -1;


}
