//next task 131d
//  main.cpp
//  Disjoint_Set_Union
//
//  Created by Иван on 29/10/2018.
//  Copyright © 2018 Иван. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector <int> parent;

//------------- DSU ------------------
void make_set(int v)
{
    parent[v] = v;
}

int find_root(int v)
{
    if (v == parent[v]) return v;   // возвращаем Лидера множества - корень
    return find_root(parent[v]);    // если сама вершина - не корень, идем вверх по родителя до корня
}

void unite_sets(int a, int b)   // множество, сод эл х и мн-во сод эл у
{
    a = find_root(a);
    b = find_root(b);
    if (a != b)
    {
        parent [b] = a;
    }
}

void WritingFromFileToArray(string input_file_path, vector <int> (*p) )
{
    ifstream input_file;
    input_file.open(input_file_path);
    
    if (!input_file.is_open())
    {
        cout << "ERROR!! The file isn't open" << endl;
    }
    else
    {
        int n;
        input_file >> n; // вершин
        
        (*p).resize(n);
        
        for ( int v = 0; v < (*p).size(); v++ ) // Петли изначально
            (*p)[v] = v;
        
        while (!input_file.eof())
        {
            int a, b;
            input_file >> a >> b ;
        
            a--;
            b--;
        
            unite_sets(a, b);
        }
        input_file.close();
    }
}

//=======================================
int main(int argc, const char * argv[]) {
    WritingFromFileToArray("input.txt", &parent);
    
    //for (int i=0; i<parent.size(); i++)
    //    cout << "  " << i+1 << " -- " << parent[i] + 1<< endl;
    for (int i=0;i<parent[i]; i++)
    {
        parent[i] = (find_root(i) == i) ? find_root(i) : i;
    }
    
    // kstd::for_each(parent.begin(), parent.end(), [](int i){ } )
    // out
   // for (int i=0; i<parent.size(); i++)
    //    cout << "  " << i+1 << " -- " << parent[i] + 1<< endl;
    
    // out for every vertex
    for (int i=0; i<parent.size(); i++)
    {
        cout << "  " << i+1 << " -- ";
        for (int j=0; j < parent.size(); j++)
            if (( i!=j ) && ( parent[i] == parent[j] ))
                cout << j+1 << " ";
    }
    
    return 0;
}
