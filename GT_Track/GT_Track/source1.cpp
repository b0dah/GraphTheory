//


//#include <bits/stdc++.h>
#include <string>
#include <set>
#include <queue>
#include <iostream>

//#define lli long long int
//#define mod 1000000007
//#define inf 1000000

using namespace std;

struct Node
{
    int x,y;
    int d, mask;
    string s;
};

struct compare
{
    bool operator () (Node a, Node b)
    {
        if (a.d==b.d) {
            return (a.s>b.s);
        }
        else {
            return (a.d>b.d);
        }
    }
};

int distance(int x, int y, int a, int b)  // расстояние между двумя ячейками
{
    return (abs(x-a)+abs(y-b));
}

const int mx=55;
string a[mx];

int n, m, k, sx, sy, tx, ty;

int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};

bool safe (int x, int y)
{
    return (x>=0 && x<n && y>=0 && y<m && a[x][y]!='S');
}

int countBit (int n)
{
    int ans=0;
    while (n>0) {
        int d=n%2;
        n=n/2;
        ans=ans+(d==1);
    }
    return ans;
}
//---------------------------------------------------------------

string bfs ()
{
    Node r={sx, sy, distance(sx, sy, tx, ty), 0, ""};
    
    priority_queue<Node, vector<Node>, compare> que; // очередь
    
    set <pair<int, pair<int, int> > > s;
    
    que.push(r);
    
    while (que.empty()==false) {
        r=que.top();
        que.pop();
        if (a[r.x][r.y]=='T') {
            return r.s;
        }
        
        if (s.find(make_pair(r.mask, make_pair(r.x, r.y)))!=s.end()) {
            continue;
        }
        
        s.insert(make_pair(r.mask, make_pair(r.x, r.y)));
        
        for (int i=0; i<4; i++) {
            int row=r.x+dx[i];
            int col=r.y+dy[i];
            
            if (safe(row, col)==false) {
                continue;
            }
            if (row==tx && col==ty) {
                return r.s;
            }
            
            int next=r.mask | (1<<(a[row][col]-97));
            
            if (countBit(next)<=k) {
                Node temp;
                temp.x=row; temp.y=col; temp.s=r.s+a[row][col];
                temp.d=distance(row, col, tx, ty)+r.s.length();
                temp.mask=next;
                que.push(temp);
            }
        }
        
    }
    return "-1";
}


int main ()
{
    cin>>n>>m>>k;
    for (int i=0; i<n; i++) {
        cin>>a[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (a[i][j]=='S') {
                sx=i;
                sy=j;
            }
            else if (a[i][j]=='T') {
                tx=i;
                ty=j;
            }
        }
    }
    //------------------------------------
    cout<<bfs();
    return 0;
}
