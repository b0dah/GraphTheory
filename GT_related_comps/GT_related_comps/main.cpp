//#include <bits/stdc++.h>
#include <utility>
#include <set>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;


set < int > del_edges[200005]; // Множество отсутсвующих ребер для каждой вершины
set < int > not_visited_vertex; // Множество непосещенных вершин
int cur_comp_count; // Кол-во вершин в текущей компоненте связности

void bfs(int v){
    queue < int > q;
    q.push(v);
    not_visited_vertex.erase(v);
    
    while ( !q.empty() ){
        v = q.front();
        q.pop();
        cur_comp_count++;
        
        vector < int > neighbors;
        
        for ( auto it : not_visited_vertex )
            if ( del_edges[v].find(it) == del_edges[v].end()){ // Если ребро есть
                neighbors.push_back(it);
                q.push(it);
            }
        
        for ( auto it : neighbors )
            not_visited_vertex.erase(it);
    }
}

int main(){
    // Ускоряем cin cout
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    int a, b;
    while ( m-- ){
        cin >> a >> b;
        a--;
        b--;
        del_edges[a].insert(b);
        del_edges[b].insert(a);
    }
    
    for(int i = 0; i < n; i++)
        not_visited_vertex.insert(i);
    
    multiset < int > result;
    for( int i = 0; i < n; i++)
        if ( not_visited_vertex.find(i) != not_visited_vertex.end() ){
            cur_comp_count = 0;
            bfs(i);
            result.insert(cur_comp_count);
        }
    
    cout <<    result.size() << '\n';
    for (auto it : result)
        cout << it << ' ';
    
}
