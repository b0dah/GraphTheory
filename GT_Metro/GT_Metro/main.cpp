//
//  main.cpp
//  GT_Metro
//
//  Created by Иван Романов on 06/01/2019.
//  Copyright © 2019 Иван Романов. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

enum colors {
    white,
    grey,
};

struct vertex {
    colors color;
    int dist;
    set <int> neighbours;
};

vector <vertex> graph;

set <int> cycle;
stack <int> s;
bool cycle_found = false;


void dfs(int v, int parent = -1 )   {         // v — вершина, в которой мы сейчас находимся
    graph[v].color = grey;
    int current;
    s.push(v);   // добавляем очередную вершину в стек
    
    for (auto it = graph[v].neighbours.begin(); it != graph[v].neighbours.end() && !cycle_found; it++) {
        current = *it;
        if ( current != parent ) {  // текущее рассматриваемое из вершины ребро не являетя тем ребром, по которому пришли в эту вершину?
            if (graph[current].color == white)
                dfs(current, v);
            else {  // иначе - цикл
                cycle.insert(current);
                while (s.top() != current) { // послед выстаскиваем вершины, сост цикл
                    cycle.insert(s.top());
                    graph[s.top()].dist = 0;
                    s.pop(); // вытаскиваем очередную вершину цикла
                }
                cycle_found = true;
            }
        }
    }
    s.pop();
}


int main(int argc, const char * argv[]) {
    
    int n = 4;
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
//-------------------------------------------------
    for ( auto it : graph ) // ответ
        cout << it.dist << ' ';
    
    return 0;
}
