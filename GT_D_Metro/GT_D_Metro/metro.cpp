//#include <bits/stdc++.h>
#include <set>
#include <queue>
#include <vector>
#include <array>
#include <stack>
#include <iostream>
using namespace std;


enum t_color{
    white,
    gray,
};

struct vertex{
    t_color color;
    int range;    // Расстояние до цикла
    set < int > neigbors;
};

vector < vertex > graph;
set < int > cicle;
stack <int> s;
bool enough = false;

int dfs(int v, int parent = -1 ){
    graph[v].color = gray;
    s.push(v);
    int cur;
    for ( auto it = graph[v].neigbors.begin(); it != graph[v].neigbors.end() && ! enough; it++ ){
        cur = *it;
        if ( cur != parent ){
            if ( graph[cur].color == white )
                dfs(cur,v);
            else{
                cicle.insert(cur);
                while ( s.top() != cur ){
                    cicle.insert(s.top());
                    graph[s.top()].range = 0;
                    s.pop();
                };
                enough = true;
            }
        }
        
    }
    s.pop();
    return 0;
}

int bfs(int v){
    stack <int> s;
    set<int> visited;
    s.push(v);
    visited.insert(v);
    int cur;
    while ( ! s.empty() ){
        cur  = s.top();
        s.pop();
        for( auto it : graph[cur].neigbors )
            if ( visited.find(it) == visited.end() ){ // Если еще не посещали
                s.push(it);
                visited.insert(it);
                if ( graph[it].color == white )       // Если значение range не определено
                    graph[it].range = graph[cur].range + 1;
                else
                    graph[it].range = min(graph[it].range, graph[cur].range + 1);
            }
        
    }
    return 0;
}

int read(){
    int x=0;char c;
    for (;c<'0'||c>'9';c=getchar());
    for (;c>='0'&&c<='9';c=getchar())x=x*10+c-48;
    return x;
}

int main()
{
    // Ускоряем cin cout
    //ios::sync_with_stdio(false);
   // cin.tie(NULL);
  //  cout.tie(NULL);
    
    int n = read();
    graph.resize(n);
    for (int i = 0; i < n; i++ )
        graph[i].color = white;
    
    
    
    int a,b;
    int i = n;
    while( i-- ){
        a = read();
        b = read();
        a--;
        b--;
        graph[a].neigbors.insert(b);
        graph[b].neigbors.insert(a);
        
    }
    
    dfs(0);
    
    
    for (int i = 0; i < n; i++ )
        graph[i].color = ( cicle.find(i) == cicle.end() )? white : gray;
    
    
    bfs(*cicle.begin());
    
    for ( auto it : graph )
        cout << it.range << ' ';
    
    return 0;
}
