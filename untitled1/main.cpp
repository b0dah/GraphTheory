#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int n,m,k, is, js, it, jt;
int idir, jdir;

int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};



//vector<vector<char>> Track;
string Track[55];

struct vertex {
    string value = " ";
    //vertex *parent; //vertex *first = NULL, *second = NULL;
    vector <vertex*> neigh = {NULL, NULL, NULL, NULL};
    vertex *parent = NULL;
    vector < pair<int, int> > prev_cells;
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

/*void matrixOutPut(vector <vector<char>> a) {

    for (int i=0;i<a.size();i++) {
        for (int j=0;j<a[i].size();j++) {
            cout << a[i][j]<< "  ";
        }
        cout << endl;
    }
}*/

int sign(int x) { return (x<0) ? (-1) : (1); }

bool safe (int x, int y)
{
    return (x>=0 && x<n && y>=0 && y<m && Track[x][y]!='S');// && Track[x][y]!='T');// && ((x<=is && x<=it) || (x>=is && x>=it)) );
    //while (! (i == it && j == jt)); //|| (abs(i - it) == 1 && j == jt) || (i == it && abs(j - jt) == 1 ) ));
}

/*void add_node(int i, int j, vertex *&Tree) { // ветвление, перевод в дерево
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

}*/

bool pair_in_vector (vector<pair<int,int>> a, pair<int, int> pr) {
    for (int i=0;i<a.size();i++){
        if ( a[i].first == pr.first && a[i].second == pr.second ) return true;

    }
    return false;
}

void add_node(int x, int y, vertex *&Tree) { // +****************************

    if (NULL == Tree)             // Если дерева НЕТ, то ложим семечко
    {
        Tree = new vertex;              //Выделяем память под звено дерева
        Tree->value = "";                  //Записываем 'S'(пустоту) в звено
        Tree->neigh = {NULL, NULL, NULL, NULL};   //Подзвенья инициализируем пустотой во избежание ошибок
        Tree->parent = Tree; //***
        Tree->prev_cells.push_back({x,y});
        //cout << "jopr";
    }


    for (int i=0;i<4;i++) {

        int row = x + dx[i];
        int col = y + dy[i];


        if (safe(row, col) && !(row==Tree->prev_cells.end()->first && col==Tree->prev_cells.end()->second) ) {   // напр на нового соседа

            //if (find(Tree->prev_cells.begin(), Tree->prev_cells.end(), {row, col}) != Tree->prev_cells.end() )
            if (pair_in_vector(Tree->prev_cells, {row, col}))
                continue;

            Tree->neigh[i] = new vertex;               //Выделяем память i подзвену. Именно подзвену, а не просто звену
            Tree->neigh[i]->neigh = {NULL, NULL, NULL, NULL}; //У  подзвена будут свои подзвенья, инициализируем их пустотой
            Tree->neigh[i]->value = Tree->value + Track[row][col];                   //Записываем в подзвено  элемент

            Tree->neigh[i]->prev_cells = Tree->prev_cells;
            Tree->neigh[i]->prev_cells.push_back({row, col});

            //cout<< Tree->neigh[i]->value<<endl;
            Tree->neigh[i]->parent = Tree; //***
            if (Track[row][col] == 'T') return;

            add_node(row, col, Tree->neigh[i]);
        }
    }
}

/*void show_tree(vertex *&Tree)              //Функция показа
{
    if (Tree != NULL)               //Пока не встретится пустое звено
    {

        cout << Tree->value << " -  \n";             //Отображаем корень дерева
        show_tree(Tree->first);               //Рекурсивная функция для вывода левого поддерева
        show_tree(Tree->second);               //Рекурсивная функци для вывода правого поддерева
    }
}*/

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

    if ( s.size() > k+1 ) return true;
    else return false;
}


void cut_tree(vertex *&Tree)              //Функция обхода
{
    if (Tree != NULL )
    {
        for (int i=0; i<4; i++) {
            if (Tree->neigh[i] != NULL && need_to_cut(Tree->neigh[i]))

                //cout << "cut";
                //cout << Tree->first->value << "-";
                Tree->neigh[i] = NULL;  // cutting the rope
            //cout << endl;

            cut_tree(Tree->neigh[i]);  // (от первого соседа соседа)            //Рекурсивная функция для поддерева
        }
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

void comparison(vertex *Tree, set <string> &char_set, int &min_length/* m*n */)
{
    if (Tree != NULL ) {
        for (int i=0;i<4;i++) {
            if (  (Tree->value[Tree->value.length()-1] == 'T') && (Tree->value.length()<min_length) ) {
                min_length = Tree->value.length();
                string str_copy = Tree->value;  // ****
                str_copy.resize(str_copy.size()-1);
                char_set.insert(str_copy); //**
                //cout << "<<"<<Tree->value << ">>"<<endl;
            }
            //-------------------------
            comparison(Tree->neigh[i], *&char_set, *&min_length); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
        }
    }
}
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
int main(int argc, const char * argv[]) {

    //WritingFromFileToMatrix("input.txt", n, m, k);
    //cout << " ---))) "<<endl;
    cin>>n>>m>>k; //input
    for (int i=0; i<n; i++)
        cin>>Track[i];


    /*n=5, m=3, k=2;


    Track[0][0] = 'S';
    Track[0][1] = 'b';
    Track[0][2] = 'a';


    Track[1][0] = 'c';
    Track[1][1] = 'c';
    Track[1][2] = 'c';


    Track[2][0] = 'a';
    Track[2][1] = 'a';
    Track[2][2] = 'c';


    Track[3][0] = 'c';
    Track[3][1] = 'c';
    Track[3][2] = 'c';

    Track[4][0] = 'a';
    Track[4][1] = 'b';
    Track[4][2] = 'T';*/


    //matrixOutPut(Track);
    /*cout<< endl<<endl;
    for (int i=0;i<n;i++)
        cout<<Track[i]<<endl;*/

//===================================================================
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (Track[i][j] == 'S') { is = i; js = j; }
            if (Track[i][j] == 'T') { it = i; jt = j; }
        }
    } // directions

    //length = abs(it - is) + abs(jt - js) + 1;
    //idir = sign(it - is);
    //jdir = sign(jt - js);

//*1*----- to Tree -----------------------------------------------
    add_node(is,js, Tree); // от 'S'
//*2*----- cuttng ---
    cut_tree(Tree);

//*3* ----- min length and lexicography min--------
    set <string> str_set;
    int min_length = m*n;
    comparison(Tree, str_set, min_length);

//** --- OUTPUT
    //cout <<endl;
    if (!str_set.empty())
        cout<<*str_set.begin() << endl;
    else cout << "-1";


//----------------------------------------------------------------
    return 0;
}
