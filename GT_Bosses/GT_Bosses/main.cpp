//#include <bits/stdc++.h>
#include <set>
#include <queue>
#include <vector>
#include <iostream>

#define pb push_back

using namespace std;

struct vertex{
    int color;
    int rank; //время
    int great_parent; // старший родитель
    int mx;      // Max bridge count
    vector<int> neigbors;
    
    vertex(){
        color = 0;
        rank  = 0;
        mx    = 0;
    }
};

//array < vertex , 500043 > graph;
vertex graph [500043];
int ans = 0;


void dfs_bridge(int root, int parent = -1, int timer =  0) {
    graph[root].color = 1;                        // Посещаем текущую вершину
    graph[root].rank = graph[root].great_parent = timer;   // Задаем текущее время, "старший" родитель root - root
    for ( auto i : graph[root].neigbors ){   // Идем по всем соседям
        if ( i != parent) {     // Исключая parent
            if (graph[i].color)     // Если сосед посещен
                graph[root].great_parent = min(graph[root].great_parent, graph[i].rank);// Запоминаем его время (т.к. сосед просмотренный, то rank у него меньше )
            else {   // Иначе
                dfs_bridge(i, root, timer + 1);  // Вычисляем "старшего" родителя вершины i
                graph[root].great_parent = min(graph[root].great_parent, graph[i].great_parent); // Т.к i - сосед root, то "старший" родитель i есть также старший родитель root
                // Если root "старше" самого старшего родителя i, то ребро (root,i) - мост, добавим 1 VVV
                ans =max(ans , graph[root].mx + graph[i].mx + ( graph[i].great_parent>graph[root].rank ) ); // В итоге Ans = max глубины мостов в поддеревьях root + пред max глубины мостов в поддеревьях root
                graph[root].mx = max (graph[root].mx, graph[i].mx + ( graph[i].great_parent>graph[root].rank ) ); // Вычисляем max глубину мостов в "текущем" поддереве
                
            }
        }
    }
}

int main(){
    // Ускоряем cin cout
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    int a,b;
    while ( m-- ){
        cin >> a >> b;
        //a--;
        //b--;
        graph[a].neigbors.pb(b);
        graph[b].neigbors.pb(a);
    }
    
    dfs_bridge(1);
    
    cout << ans;
}
