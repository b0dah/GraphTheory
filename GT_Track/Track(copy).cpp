#include <bits/stdc++.h>

using namespace std;

short int n,m,k, is, js;//it, jt;
// short int idir, jdir;

short int dx[]={0, 0, 1, -1};
short int dy[]={1, -1, 0, 0};


//vector<vector<char>> Track;
string Track[50];

struct vertex {
    //string value = " ";
    //vertex *parent; //vertex *first = NULL, *second = NULL;
    //vector <vertex*> neigh = {NULL, NULL, NULL, NULL};
    vertex *neigh[4] = {NULL, NULL, NULL, NULL};
    //vertex *parent = NULL;
    vector < pair<char, char> > prev_cells;;
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
 for (short int i = 0; i < n; i++) //
 {
 Track[i].resize(m);
 for (short int j = 0; j < m; j++)
 {
 input_file>> Track[i][j];
 }
 }
 input_file.close();
 }*/

/*void matrixOutPut(vector <vector<char>> a) {
 
 for (short int i=0;i<a.size();i++) {
 for (short int j=0;j<a[i].size();j++) {
 cout << a[i][j]<< "  ";
 }
 cout << endl;
 }
 }*/

//short int sign(short int x) { return (x<0) ? (-1) : (1); }

bool safe (char x, char y)
{
    return (x>=0 && x<n && y>=0 && y<m && Track[x][y]!='S');// && Track[x][y]!='T');// && ((x<=is && x<=it) || (x>=is && x>=it)) );
    //while (! (i == it && j == jt)); //|| (abs(i - it) == 1 && j == jt) || (i == it && abs(j - jt) == 1 ) ));
}

/*void add_node(short int i, short int j, vertex *&Tree) { // ветвление, перевод в дерево
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

bool pair_in_vector (vector<pair<char,char> > a, pair<char, char> pr) {
    for (char i=0;i<a.size();i++)
        if ( a[i].first == pr.first && a[i].second == pr.second ) return true;
    return false;
}
    

bool number_of_unique_symbols_more_than_k(vector<pair<char,char> > a){
    set <char> s;
    for (char ind=0;ind<a.size();ind++)
    {   s.insert(Track [a[ind].first][a[ind].second] );   }
    return (s.size()> k+1);
}

void add_node(char x, char y, vertex *&Tree) { // +****************************
    
    if (NULL == Tree)             // Если дерева НЕТ, то ложим семечко
    {
        Tree = new vertex;              //Выделяем память под звено дерева
        //Tree->value = "";                  //Записываем 'S'(пустоту) в звено
        //Tree->neigh = {NULL, NULL, NULL, NULL};   //Подзвенья инициализируем пустотой во избежание ошибок
        for (char ind=0;ind<4;ind++){
            Tree->neigh[ind] = NULL; //=====**
        }
        //Tree->parent = Tree; //***
        //Tree->prev_cells.push_back(make_pair(x,y));
        Tree->prev_cells.push_back(make_pair(x,y));
        //cout << "jopr";
    }
    
    
    for (char i=0;i<4;i++) {
        
        short int row = x + dx[i];
        short int col = y + dy[i];
        
        
        if (safe(row, col)) { //&& !(row==Tree->prev_cells.end()->first && col==Tree->prev_cells.end()->second) ) {   // напр на нового соседа
            
            //if (find(Tree->prev_cells.begin(), Tree->prev_cells.end(), {row, col}) != Tree->prev_cells.end() )
            if (pair_in_vector(Tree->prev_cells, make_pair(row, col) ) )
                continue;
            
            Tree->neigh[i] = new vertex;               //Выделяем память i подзвену. Именно подзвену, а не просто звену
            //Tree->neigh[i]->neigh = {NULL, NULL, NULL, NULL}; //У  подзвена будут свои подзвенья, инициализируем их пустотой
            for (char ind=0;ind<4;ind++)   {   Tree->neigh[i]->neigh[ind] = NULL;   }//==**
            
            //Tree->neigh[i]->value = Tree->value + Track[row][col];                   //Записываем в подзвено  элемент
            
            Tree->neigh[i]->prev_cells = Tree->prev_cells;
            Tree->neigh[i]->prev_cells.push_back(make_pair(row, col));
            
            //////////////////////
            /*set <char> s;
             for (char ind=0;ind<Tree->neigh[i]->prev_cells.size();ind++)
             {   s.insert(Track [Tree->neigh[i]->prev_cells[ind].i][Tree->neigh[i]->prev_cells[ind].j] );   }
             if (s.size()> k+1){
             //cout << "cncld -> "  <<Tree->neigh[i]->value <<endl;*/
            if (number_of_unique_symbols_more_than_k(Tree->neigh[i]->prev_cells))
                continue;
            
            //////////////////////
            
            //cout<< Tree->neigh[i]->value<<endl;
            //Tree->neigh[i]->parent = Tree; //***
            if (Track[row][col] == 'T') {
                return;
            }
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

/*bool need_to_cut(vertex *Tree)
 {
 set <char> s;
 
 for (char ind=0; ind<Tree->value.length();ind++)   // количество уникальных символов в пути
 s.insert(Tree->value[ind]);
 
 if ( s.size() > k+1 ) { cout << "was"; return true;  }
 else return false;
 }*/

/*void del(Node *&Tree){
 if (Tree != NULL)                //Пока не встретится пустое звено
 {
 del(Tree->l);                //Рекурсивная функция прохода по левому поддереву
 del(Tree->r);                //Рекурсивная функци для прохода по правому поддереву
 delete Tree;                 //Убиваем конечный элемент дерева
 Tree = NULL;                 //Может и не обязательно, но плохого не будет
 }*/

/*void cut_tree(vertex *&Tree)              //Функция обхода
 {
 if (Tree != NULL )
 {
 for (char i=0; i<4; i++) {
 if (Tree->neigh[i] != NULL && need_to_cut(Tree->neigh[i]))
 
 //cout << "cut";
 //cout << Tree->first->value << "-";
 
 //delete Tree->neigh[i];
 
 /*for (char j=0; j<4; j++) {
 if (Tree->neigh[i]->neigh[j] != NULL )
 delete Tree->neigh[i]->neigh[j];
 }
 Tree->neigh[i] = NULL;  // cutting the rope
 
 //cout << endl;
 
 cut_tree(Tree->neigh[i]);  // (от первого соседа соседа)            //Рекурсивная функция для поддерева
 
 }
 }
 }*/

/*string min_string(string s1, string s2)
 {
 for (short int i=0; i<s1.length();i++)
 {
 if (s1[i]<s2[i]) {
 return s1;
 break;
 }
 }
 return s2;
 }*/

/*void comparison(vertex *Tree, set <string> &char_set, short int &min_length )
 {
 if (Tree != NULL ) {
 for (char i=0;i<4;i++) {
 if ( ( Tree->value!= "") && (Tree->value[Tree->value.length()-1] == 'T') && (Tree->value.length()<=min_length) ) {
 min_length = Tree->value.length();
 string str_copy = Tree->value;  // ****
 str_copy.resize(str_copy.size()-1);
 char_set.insert(str_copy);
 //cout << "<<"<<Tree->value << ">>"<<endl;
 }
 //-------------------------
 comparison(Tree->neigh[i], *&char_set, *&min_length); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
 }
 }
 }*/

void comparison(vertex *Tree, set <string> &char_set, short int &min_length/* m*n */)
{
    if (Tree != NULL ) {
        for (char i=0;i<4;i++) {
            if ( ( Tree->prev_cells.size()>1) && ( Track [ Tree->prev_cells[Tree->prev_cells.size()-1].first ] [Tree->prev_cells[Tree->prev_cells.size()-1].second ] == 'T') ) {
                if (Tree->prev_cells.size()<=min_length)  {
                    min_length = Tree->prev_cells.size();
                    
                    string str;
                    for (char ind=1;ind< Tree->prev_cells.size()-1; ind++){
                        str+= Track [Tree->prev_cells[ind].first][Tree->prev_cells[ind].second];
                    }
                    
                    char_set.insert(str); //**
                    //cout << "<<"<<Tree->value << ">>"<<endl;
                }
            }
            //-------------------------
            comparison(Tree->neigh[i], *&char_set, *&min_length); // (от второго соседа соседа)            //Рекурсивная функци для вывода правого поддерева
        }
    }
}
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
int main(int argc, const char * argv[]) {
    
    //WritingFromFileToMatrix("input.txt", n, m, k);
    /*Tree->neigh.resize(4);
     for (short int ind=0;ind<4;ind++){
     Tree->neigh[ind] = NULL; //=====**
     }*/
    //------------------------------
    cin>>n>>m>>k; //input
    for (char i=0; i<n; i++)
        cin>>Track[i];
    
    
    
    //matrixOutPut(Track);
    /*cout<< endl<<endl;
     for (short int i=0;i<n;i++)
     cout<<Track[i]<<endl;*/
    
    //===================================================================
    for (char i=0;i<n;i++) {
        for (char j=0;j<m;j++) {
            if (Track[i][j] == 'S') { is = i; js = j; }
        }
    } // directions
    
    //length = abs(it - is) + abs(jt - js) + 1;
    //idir = sign(it - is);
    //jdir = sign(jt - js);
    
    //*1*----- to Tree -----------------------------------------------
    add_node(is,js, Tree); // от 'S'
    //*2*----- cuttng ---
    //cut_tree(Tree);
    
    //*3* ----- min length and lexicography min--------
    set <string> str_set;
    short int min_length = m*n;
    comparison(Tree, str_set, min_length);
    
    //** --- OUTPUT
    //cout <<endl;
    //cout<<"=|>";
    if (!str_set.empty())
        cout<<*str_set.begin() << endl;
    else cout << "-1";
    
    //----------------------------------------------------------------
    return 0;
}
