//
//  main.cpp
//  GT_D_Metro
//
//  Created by Иван Романов on 25/12/2018.
//  Copyright © 2018 Иван Романов. All rights reserved.
//

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
    grey,
};

struct vertex{
    t_color color;
    int dist;    // Расстояние до цикла
    set < int > neighbours;
};

vector < vertex > graph;

set < int > cycle;
stack <int> s;
bool cycle_found = false;

int dfs(int v, int parent = -1 ){   // v — вершина, в которой мы сейчас находимся
    graph[v].color = grey;
    
    s.push(v); // добавляем очередную вершину в стек
    int current;
    
    for ( auto it = graph[v].neighbours.begin(); it != graph[v].neighbours.end() && ! cycle_found; it++ ){
        current = *it;
        if ( current != parent ){ // текущее рассматриваемое из вершины ребро не являетя тем ребром, по которому пришли в эту вершину?
            if ( graph[current].color == white )
                dfs(current,v);
            else{ // иначе - цикл
                cycle.insert(current);
                while ( s.top() != current ){ // послед выстаскиваем вершины, сост цикл
                    cycle.insert(s.top());
                    graph[s.top()].dist = 0;
                    s.pop();    // вытаскиваем очередную вершину цикла
                };
                cycle_found = true;
            }
        }
        
    }
    if (! s.empty()) s.pop();
    return 0;
}

int bfs(int v){
    stack <int> s;
    set<int> visited;
    
    s.push(v);
    visited.insert(v);
    
    int current;
    
    while ( ! s.empty() ){
        current  = s.top(); // достали верхушку
        s.pop();            //
        for( auto it : graph[current].neighbours )
            if ( visited.find(it) == visited.end() ){ // Если еще не посещали (iter == end - когда отсутсвует во множестве)
                s.push(it);
                visited.insert(it);
                if ( graph[it].color == white )       // Если значение dist не определено (если не на цикле лежит)
                    graph[it].dist = graph[current].dist + 1;
                else
                   graph[it].dist = min(graph[it].dist, graph[current].dist + 1);
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
   ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    /*int n = read();
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
        graph[a].neighbours.insert(b);
        graph[b].neighbours.insert(a);
    }
 */
 
 /*   int n = 4;
    graph.resize(n);
    for (int i = 0; i < n; i++ )
        graph[i].color = white;
    
    
    graph[0].neighbours.insert(2);
    graph[2].neighbours.insert(0);
    
    graph[3].neighbours.insert(2);
    graph[2].neighbours.insert(3);
    
    graph[3].neighbours.insert(1);
    graph[1].neighbours.insert(3);
    
    graph[0].neighbours.insert(1);
    graph[1].neighbours.insert(0);
 */
    
    int n = 5;
    graph.resize(n);
    for (int i = 0; i < n; i++ )
        graph[i].color = white;
    
    
    graph[0].neighbours.insert(2);
    graph[2].neighbours.insert(0);
    
    graph[0].neighbours.insert(4);
    graph[4].neighbours.insert(0);
    
    graph[3].neighbours.insert(1);
    graph[1].neighbours.insert(3);
    
    graph[1].neighbours.insert(2);
    graph[2].neighbours.insert(1);
    
    graph[4].neighbours.insert(1);
    graph[1].neighbours.insert(4);
//======================================================================
    dfs(0);
    
    
    for (int i = 0; i < n; i++ )
        graph[i].color = ( cycle.find(i) == cycle.end() ) ? white : grey; // если не в цикле, то белые
    
    
    bfs(*cycle.begin());  // поиск расстояний для каждой вершины
    
    for ( auto it : graph ) // ответ
        cout << it.dist << ' ';
}
