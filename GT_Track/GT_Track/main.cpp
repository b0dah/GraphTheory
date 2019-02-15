//
//  main.cpp
//  GT_Track
//
//  Created by Иван Романов on 23/12/2018.
//  Copyright © 2018 Иван Романов. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int n,m,k;
int idir, jdir;
//vector<vector<char>> Track;
char Track[50][50];

struct vertex {
    string value = " ";
    vertex *parent;
    vertex *first = NULL, *second = NULL;
};

vertex *Tree = NULL; // инициализация дерева

/*void WritingFromFileToMatrix(string file_path, int &n, int &m, int &k)
{
    //-------------------------------------------------------
    ifstream input_file;
    
    input_file.open(file_path);
    
    if (!input_file.is_open()) {
        cout << "error file"<< endl;
        return;
    }

    input_file >> n>>m>>k; //вершин & ребер
    
    Track.resize(n);
    for (int i = 0; i < n; i++) //
    {
        Track[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            input_file>> Track[i][j];
        }
    }
    input_file.close();
}*/

void matrixOutPut(vector <vector<char>> a) {
    
    for (int i=0;i<a.size();i++) {
        for (int j=0;j<a[i].size();j++) {
            cout << a[i][j]<< "  ";
        }
        cout << endl;
    }
}

int sign(int x) { return (x<0) ? (-1) : (1); }

bool safe (int x, int y)
{
    return (x>=0 && x<n && y>=0 && y<m && Track[x][y]!='S' && Track[x][y]!='T');
    //while (! (i == it && j == jt)); //|| (abs(i - it) == 1 && j == jt) || (i == it && abs(j - jt) == 1 ) ));
}

void add_node(int i, int j, vertex *&Tree) { // ветвление, перевод в дерево
    if (NULL == Tree)             // Если дерева НЕТ, то ложим семечко
    {
        Tree = new vertex;              //Выделяем память под звено дерева
        Tree->value = "";                  //Записываем 'S'(пустоту) в звено
        (Tree->first) = (Tree->second) = NULL;   //Подзвенья инициализируем пустотой во избежание ошибок
        
        Tree->parent = Tree;
    }
    
    if ( safe(i + idir, j) ) // "вправо"
    {
        Tree->first = new vertex;               //Выделяем память левому подзвену. Именно подзвену, а не просто звену
        Tree->first->first = Tree->first->second = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
        Tree->first->value = Tree->value + Track[i + idir][j];                   //Записываем в левое подзвено записываемый элемент
        
        Tree->first->parent = Tree;
        
        add_node(i + idir, j, Tree->first);
    }
    
    if ( safe(i, j + jdir) ) // "вниз"
    {
        Tree->second = new vertex;
        Tree->second->first = Tree->second->second = NULL;
        Tree->second->value = Tree->value + Track[i][j + jdir];
        
        Tree->second->parent = Tree;
        
        add_node(i, j + jdir, Tree->second);
    }
    
}

void show_tree(vertex *&Tree)              //Функция показа
{
    if (Tree != NULL)               //Пока не встретится пустое звено
    {
    
        cout << Tree->value << " -  \n";             //Отображаем корень дерева
        show_tree(Tree->first);               //Рекурсивная функция для вывода левого поддерева
        show_tree(Tree->second);               //Рекурсивная функци для вывода правого поддерева
    }
}

/*void observe_tree(vertex *&Tree)              //Функция обхода
{
    if (Tree != NULL) //(фест нейбор не налл И секонд нейбор не налл)              //Пока не встретится пустое звено
    {
        if (Tree->first == NULL && Tree->second == NULL)
        {
            vertex *TreeCopy = Tree;
            set <char> s;
            
            while (TreeCopy->value != "")
            {
                cout << TreeCopy->value << "-";
                //s.insert((TreeCopy->value));
                TreeCopy = TreeCopy->parent;
            }
            if ( s.size() > k ) cout << "cut";
            cout << endl;
        }
        
        observe_tree(Tree->first);  // (от первого соседа соседа)            //Рекурсивная функция для вывода левого поддерева
        observe_tree(Tree->second); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
    }
}
*/

bool need_to_cut(vertex *Tree)
{
    set <char> s;
    
    for (int ind=0; ind<Tree->value.length();ind++)   // количество уникальных символов в пути
        s.insert(Tree->value[ind]);

        if ( s.size() > k ) return true;
        else return false;
}


void cut_tree(vertex *&Tree)              //Функция обхода
{
    if (Tree != NULL )
    {
        /*1*/if (Tree->first != NULL && need_to_cut(Tree->first))
        {
                //cout << "cut";
                //cout << Tree->first->value << "-";
                Tree->first = NULL;  // cutting the rope
        }
            //cout << endl;
        /*2*/if (Tree->second != NULL && need_to_cut(Tree->second))
        {
                //cout << "cut";
                //cout << Tree->second->value << "-";
                Tree->second = NULL; // cutting
        }
        
            cut_tree(Tree->first);  // (от первого соседа соседа)            //Рекурсивная функция для вывода левого поддерева
            cut_tree(Tree->second); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
    }
}

/*string min_string(string s1, string s2)
{
    for (int i=0; i<s1.length();i++)
    {
        if (s1[i]<s2[i]) {
            return s1;
            break;
        }
    }
    return s2;
}*/

void comparison(vertex *Tree, set <string> &s)
{
    
     if (Tree != NULL ) {
        if ( Tree->value.length() == (n+m-3) ) {
            //cout << "======== THE ANSWER IS: =========="<<endl;
            //cout << "<<"<<Tree->value << ">>"<<endl;
            s.insert(Tree->value); //**
        }
    //-------------------------
        comparison(Tree->first, *&s);  // (от первого соседа соседа)            //Рекурсивная функция для вывода левого поддерева
        comparison(Tree->second, *&s); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
    }
}

int main(int argc, const char * argv[]) {
// insert code here...
    
    //WritingFromFileToMatrix("input.txt", n, m, k);
    cin>>n>>m>>k; //input
    for (int i=0; i<n; i++) {
        cin>>Track[i];
    }
    
    //matrixOutPut(Track);
//===================================================================

    int i, j, is, js, it, jt;
    
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (Track[i][j] == 'S') { is = i; js = j; }
            if (Track[i][j] == 'T') { it = i; jt = j; }
        }
    } // directions
    
    //length = abs(it - is) + abs(jt - js) + 1;
    idir = sign(it - is);
    jdir = sign(jt - js);
    
//*1*----- to Tree -----------------------------------------------
      
    add_node(is,js, Tree); // от 'S'
    cut_tree(Tree);
    
   // string str="";
   // for (int ind = 0;ind<(m+n-3);ind++){
    //    str += "z";
    //}
    set <string> str_set;
    comparison(Tree, str_set);
    
    //cout <<endl;
    if (!str_set.empty())
        cout<< *str_set.begin() << endl;
    else cout << "-1";
    
    
//----------------------------------------------------------------
    return 0;
}
