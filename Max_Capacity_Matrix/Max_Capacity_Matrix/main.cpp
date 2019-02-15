// Matrix.cpp: определяет точку входа для консольного приложения.
//

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct Vertex {
    vector<pair<int, int>> sosedi;                //Пара - вес ребра и другой конец
};
int n = 0;
int w_max = 0;
vector<Vertex> graph;
vector<int> Path;
vector<vector<int>> path_matrix;
vector<vector<int>> transmit_matrix;

int sum_vect(vector<int> P2) {
    int sum = 0;
    for (int i = 0; i < P2.size(); i++)
        if (P2[i] != w_max + 1) sum += P2[i];
    return sum;
}

int min_vect(vector<pair<int,int>> P) {
    pair<int,int> min = P[0];
    for (int i = 0; i < P.size(); i++)
        if (P[i].first <= min.first) min = P[i];
    return min.second;
}

int max_vect(vector<int> P1) {
    int k = 0;
    while (P1[k] == w_max + 1) k++;
    int max = P1[k];
    for (int i = k; i < P1.size(); i++)
        if ((P1[i] >= max) && (P1[i] != w_max + 1)) max = P1[i];
    return max;
}

int min(int a, int b) {
    if (a <= b) return a;
    else return b;
}

void Matr_Path_Build(int size, int w_max1) {
    //******************Создание матрицы****************************************
    for (int i = 0; i < size; i++) Path.push_back(w_max1 + 1);
    for (int i = 0; i < size; i++) path_matrix.push_back(Path);
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < graph[i].sosedi.size(); k++) {
            path_matrix[i][graph[i].sosedi[k].second] = graph[i].sosedi[k].first;
        }
        path_matrix[i][i] = 0;
    }
    //*****************Формирование матрицы*************************************
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (path_matrix[i][j] > path_matrix[i][k] + path_matrix[k][j]) path_matrix[i][j] = path_matrix[i][k] + path_matrix[k][j];
}
void Matr_Transmit_Build(int size, int w_max1) {
    //******************Создание матрицы****************************************
    for (int i = 0; i < size; i++) Path.push_back(w_max1 - 1);
    for (int i = 0; i < size; i++) transmit_matrix.push_back(Path);
    
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < graph[i].sosedi.size(); k++) {
            transmit_matrix[i][graph[i].sosedi[k].second] = graph[i].sosedi[k].first;
        }
    }
    //*****************Формирование матрицы*************************************
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (transmit_matrix[i][j] < min(transmit_matrix[i][k], transmit_matrix[k][j])) transmit_matrix[i][j] = min(transmit_matrix[i][k], transmit_matrix[k][j]);
    for (int i = 0; i < size; i++) {                                    // Этот цикл(по s) для того, чтобы, все то, что ниже, сделать 2 раза. Зачем?
        for (int j = 0; j < size; j++)                                // Потому что, если при первом обходе в качестве промежуточной вершины k взять еще раннее не посещенную вершину(ее пропускная способность = -беск), а через эту вершину можно получить max пропускную способность больше, чем через уже известные,
            for (int k = 0; k < size; k++)                            // то получим, в результате, не то, что нужно для этих пар вершин. Чтобы получить то, что нужно, мы еще раз делаем то же самое, т.к там уже посчитаны max пропускные способности, и они могут быть использованы(все вершины уже раннее были посещены)
                if (transmit_matrix[i][j] < min(transmit_matrix[i][k], transmit_matrix[k][j])) transmit_matrix[i][j] = min(transmit_matrix[i][k], transmit_matrix[k][j]);
        transmit_matrix[i][i] = 0;
    }
}
void Output_Matrix(vector<vector<int>> M,int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (abs(M[i][j]) < 10) cout << "   ";
            if ((abs(M[i][j]) < 100) && (abs(M[i][j]) >= 10)) cout << "  ";
            if (M[i][j] > 100) cout << " ";
            cout << M[i][j] << "    ";
        }
        cout << "\n";
    }
}
/*int Path_Vosst(int v,int b, int path_) {
    bool prov = false;
    Path.push_back(v);
    if ((path_ < 0)||((path_ == 0) && (v != b))) {
        Path.pop_back();
        return 1;
    }
    if ((path_ == 0)||(path_ == w_max + 1)) return 0;
    for (int i = 0; i < graph[v].sosedi.size(); i++) {
        if (Path_Vosst(graph[v].sosedi[i].second, b, path_ - graph[v].sosedi[i].first) == 0) {
            prov = true;
            return 0;
        };
    }
    if (!prov) {
        Path.pop_back();
        return 1;
    }
}*/
int Path_Transmit_vosst(int v, int b, int path_, int parent = -1) {
    bool prov = false;
    Path.push_back(v);
    if (v == b) return 0;
    else {
        for (int i = 0; i < graph[v].sosedi.size(); i++) {
            if ((graph[v].sosedi[i].first >= path_)&&(graph[v].sosedi[i].second != parent)) {
                if (Path_Transmit_vosst(graph[v].sosedi[i].second, b, path_, v) == 0) {
                    prov = true;
                    return 0;
                }
            }
        }
    }
    if (!prov) {
        Path.pop_back();
        return 1;
    }
    return 0;
}

int main()
{
    int m = 0;
    vector<int> F;
    //**************Формирование графа из информации в файле**********
    ifstream f_in("Information1.txt");
    f_in.seekg(0);
    while (!f_in.eof()) {
        f_in >> n;
        F.push_back(n);
    }
    f_in.close();
    n = 0;
    for (int i = 0; i < F.size(); i += 3) {
        if (F[i] > n) n = F[i];
        if (F[i + 1] > n) n = F[i + 1];
        m++;
        w_max += abs(F[i + 2]);
    }
    graph.resize(n);
    for (int i = 0; i < F.size(); i += 3) graph[F[i] - 1].sosedi.push_back(make_pair(F[i + 2], F[i + 1] - 1));
    F.clear();
    //********************Построение матриц********************************
    Path.clear();
    Matr_Path_Build(n, w_max);
    Path.clear();
    Matr_Transmit_Build(n, -w_max);
    Path.clear();
    //********************Определяемся с выбором алгоритма*****************
    int z;
    cout << "1 - OUTPUT MATRIX" << endl;
    cout << "2 - OUTPUT PATH" << endl;
    cout << "3 - CENTER AND MEDIANA" << endl;
    cin >> z;
    switch (z) {
        case 1: {
            cout << "PATH_MATRIX" << endl;
            Output_Matrix(path_matrix, n, n);
            cout << "TRANSMIT_MATRIX" << endl;
            Output_Matrix(transmit_matrix, n, n);
        }; break;
        case 2: {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    /*Path.clear();
                    cout << "\n ( " << i + 1 << " , " << j + 1 << " )";
                    cout << "               min_path - ";
                    if (path_matrix[i][j] == w_max + 1) cout << "NO PATH";
                    else cout << path_matrix[i][j];
                   // Path_Vosst(i, j, path_matrix[i][j]);
                    cout << "               ";
                    if (path_matrix[i][j] == w_max + 1) cout << "NO";
                    else for (int k = 0; k < Path.size(); k++) cout << Path[k] + 1 << " ";
                    Path.clear(); */
                    cout << endl;
                    cout << "\n ( " << i + 1 << " , " << j + 1 << " )";
                    cout << "               transmit_path - ";
                    if (transmit_matrix[i][j] == -w_max - 1) cout << "NO PATH";
                    else cout << transmit_matrix[i][j];
                    Path_Transmit_vosst(i, j, transmit_matrix[i][j]);
                    cout << "               ";
                    if (transmit_matrix[i][j] == -w_max - 1) cout << "NO";
                    else for (int k = 0; k < Path.size(); k++) cout << Path[k] + 1 << " ";
                    Path.clear();
                }
            }
        }; break;
        case 3: {
            vector<pair<int,int>> d;
            for (int i = 0; i < path_matrix.size(); i++) d.push_back(make_pair(max_vect(path_matrix[i]),i));
            cout << "CENTER = " << min_vect(d) + 1 << endl;
            d.clear();
            for (int i = 0; i < path_matrix.size(); i++) d.push_back(make_pair(sum_vect(path_matrix[i]),i));
            cout << "MEDIANA = " << min_vect(d) + 1 << endl;
            d.clear();
        }; break;
        default: break;
    }
    //system("\n pause");
    return 0;
}

