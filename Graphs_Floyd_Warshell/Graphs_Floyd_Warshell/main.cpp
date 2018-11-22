//
// FloydWashell.cpp :
// создается матрица на пересеч i j - вес
/*
 сложность n^3
 j - i - k
 
 Форд-бэллман
 */
//psya

#include <iostream>
#include <vector>
#include <fstream>
#include "math.h"


using namespace std;
#define input_file_path "input.txt"
const int INF = 100;

vector <vector <int> > paths_matrix;
vector <vector <int>> min_paths_matrix;
vector <vector<int>> next_vertex;

int CountOfDigitsInNumber(int a){ return (a!=0) ? ( log10(a) + 1) : 1; }

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void WritingFromFileToMatrix(string file_path, int *n)
{
    //-------------------------------------------------------
    ifstream input_file;
    
    input_file.open(file_path);
    
    if (!input_file.is_open())
        cout << "error file"<< endl;
    
    int m;
    input_file >> *n>>m; //вершин & ребер
    paths_matrix.resize(*n);
    
    
    for (int i = 0; i < *n; i++) //    ВСЕ = INF, а диагонали - нули
    {
        paths_matrix[i].resize(*n);
        for (int j = 0; j < *n; j++)
        {
            if (i == j) paths_matrix[i][j] = 0;
            else    paths_matrix[i][j] = INF;
        }
    }
    
    
   //while (input_file) // считывает лишний раз
    for (int j=0;j<m;j++)
    {
        int a, b, w;
        input_file >> a >> b >> w;
        
        a--;
        b--;
        
        paths_matrix[a][b] = w;
        //paths_matrix[b][a] = w;
    }
    input_file.close();
}
//-------------------------------------------------------

bool NegativeCycleIsPresent(vector<vector<int>> matrix)
{
    //---------- neg cyc -------------
    bool is_negative_cycle = false;
    
    for (int i = 0; i < matrix.size()&& (!is_negative_cycle) ; i++)
        is_negative_cycle = (matrix[i][i] != 0);
    
    return is_negative_cycle;
}


vector <vector <int>> FloydWarshall(vector <vector <int> > matrix)
{
    int n = matrix.size();
    
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                //matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                if ( matrix[i][k] + matrix[k][j] < matrix[i][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    /*!*/next_vertex[i][j] = next_vertex[i][k]; // в какую надо пойти следующей, чтобы пройти по кратч пути
                }
            
    return matrix;
}

void FillingNextMatrix(int n)
{
    next_vertex.resize(n);
    for (int i=0; i<n;i++)
    {
        next_vertex[i].resize(n);
        for (int j=0; j<n;j++)
            next_vertex[i][j] = (paths_matrix[i][j]!=0 && paths_matrix[i][j]!=INF)? j : -1;
    }
    
    vector <vector <int>> min_paths_matrix = FloydWarshall(paths_matrix);
}

void getShortestPath(int u, int v)
{
    cout << " Path from "<< u+1 << " to " << v+1<<" :  ";
    if (min_paths_matrix[u][v] == INF )
    {
        cout << "No path there"<<endl;
        return;
    }
    
    int c = u;
    while (c != v)
    {
        cout << c+1 << "->";
        c = next_vertex[c][v];
    }
    cout << v+1;
    cout << " (path length = " << min_paths_matrix[u][v]<<" )"<<endl;
}

void MatrixOutput(vector <vector <int> > matrix)
{
    cout << endl << endl << "    ";
    for (int i = 0; i < matrix.size(); i++) cout <<"   "<< i + 1 ; // columns numbers
    
    cout << endl << "    ";
    for (int i = 0; i < matrix.size(); i++) // here is "------"
        cout << "____";
    cout << endl;
    
    for (int i = 0; i < matrix.size(); i++)
    {
        cout<<i+1 <<"|  ";
        for (int j = 0; j < matrix.size(); j++)
        {
            for (int k = 0; k < 4 - CountOfDigitsInNumber(matrix[i][j]);k++)
                cout << " ";
            cout << matrix[i][j];
        }
        cout << endl;
    }
}
// ================== MAIN ===============================================
int main()
{
    int n;
    
    WritingFromFileToMatrix("input.txt", &n);
    
    FillingNextMatrix(n);
    
    min_paths_matrix = FloydWarshall(paths_matrix);
    
//============= OUTPUT ====================
    cout << "     Source Matrix:";
    MatrixOutput(paths_matrix);
    
    if (!NegativeCycleIsPresent(min_paths_matrix))
    {
        cout << endl << "     Target Matrix:";
        MatrixOutput(min_paths_matrix);
        cout << endl << "  There is NO negative cycles"<<endl<<endl;
    }
    else cout << endl<< "There is a NEGATIVE CYCLE!"<<endl;
    
    
    for (int i=0;i<n;i++) // вывод готовых путей
        for (int j=0;j<n;j++)
            if (i!=j)
                getShortestPath(i, j);
}

