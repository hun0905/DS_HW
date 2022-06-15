#include<iostream>
#include<queue>
using namespace std;
class Graph;
class Node
{
    friend class Graph;
    private:
        int data;
        Node*link;
};

class Graph
{
    public:
        ~Graph(){}
        Graph(int NumOfNode = 10){
            adLists = new Node*[NumOfNode];
            n = 0;
            e = 0;
        }
        bool IsEMpty() const{return n == 0 ;}
        int NumberOfVertices()const{return n;}
        int NumberOfEdges() const {return e;}
        int Degree(int u)const;
        bool ExistEdge(int u, int v) const;
        void InsertVertex(int v);
        void InsertEdge(int u,int v);
        void DeleteVertex(int v);
        void DeleteEdge(int u,int v);
        void DFS(int v);
        void dfs(const int v);
        void BFS(int v);
        void Components();
        void DfnLow(const int x);
        void DfnLow(const int u,const int v);
        void OutputDfn();
        void Outputlow();
    private:
        int n;
        int e;
        Node**adLists;
        bool *visited;
        int *dfn;
        int *low;
        int num;
};
void Graph::InsertVertex(int v)
{
    adLists[v] = new Node;
    adLists[v]->data = v;
    n++;
}
void Graph::DeleteVertex(int v)
{
    for(Node *i =  adLists[v] ; i != NULL ; )
    {
        int tmp = i->data;
        DeleteEdge(v,tmp);
        i = i ->link;
    }
    delete adLists[v];
    n--;
}
void Graph::InsertEdge(int u,int v)
{
    Node *n = new Node;
    n->data =v;
    n->link =NULL;
    for(Node *i =  adLists[u] ; i != NULL ; i=i->link)
    {
        if(i->link == NULL)
        {
            i->link = n;
            break;
        }
    }
    Node *n2 = new Node;
    n2->data = u;
    n2->link =NULL;
    for(Node *i =  adLists[v] ; i != NULL ; i=i->link)
    {
        if(i->link == NULL)
        {
            i->link = n2;
            break;
        }
    }
    e++;
}
void Graph::DeleteEdge(int u,int v)
{
    for(Node *i =  adLists[u] ; i != NULL ; i=i->link)
    {
        if(i->link->data == v)
        {
            Node *tmp = i->link;
            i->link = i->link->link;
            delete tmp;
        }
    }
    for(Node *i =  adLists[v] ; i != NULL ; i=i->link)
    {
        if(i->link->data == u)
        {
            Node *tmp = i->link;
            i->link = i->link->link;
            delete tmp;
        }
    }
    e--;
}
void Graph::DFS(int v)
{
    visited = new bool[n];
    fill(visited,visited+n,false);
    dfs(v);
    delete []visited;
}
void Graph::dfs(const int v)
{
    visited[v] = true;
    cout<<adLists[v]->data<<" ";
    for(Node *w = adLists[v]->link;w != NULL;w = w->link)
    {
        if(!visited[w->data])dfs(w->data);
    }
}
void Graph::BFS(int v)
{
    visited = new bool[n];
    fill(visited,visited+n,false);
    visited[v] = true;
    queue<int>q;
    q.push(v);
    while(!q.empty()){
        v = q.front();
        cout<<v<<" ";
        q.pop();
        for(Node *w = adLists[v]->link;w != NULL;w = w->link)
        {
            if(!visited[w->data]){
                q.push(w->data);
                visited[w->data] = true;
            }
            
        }
    }
    delete []visited;
}
void Graph::Components()
{
    visited = new bool[n];
    fill(visited,visited+n,false);
    for(int i = 0 ; i < n ; i++)
    {
        if(!visited[i]){
            dfs(i);
            cout<<endl;
            //OutputNewComponent();
        }
    }
    //delete []visited;
}
void Graph::DfnLow(const int x)
{
    num = 1;
    dfn = new int[n];
    low = new int[n];
    fill(dfn,dfn+n,0);
    fill(low,low+n,0);
    DfnLow(x,-1);
    cout<<"Dfn: "<<endl;
    OutputDfn();
    cout<<"low: "<<endl;
    Outputlow();
    delete []dfn;
    delete []low;
}
void Graph::DfnLow(const int u , const int v)
{
    dfn[u]=low[u]=num++;
    for(Node *w = adLists[u]->link;w != NULL;w = w->link)
    {
        if(dfn[w->data] == 0){
            DfnLow(w->data,u);
            low[u] = min(low[u],low[w->data]);
        }
        else if(w->data!=v)low[u]=min(low[u],dfn[w->data]);  
    }
}
void Graph::OutputDfn()
{
    int i = 0;
    int j = 0;
    while(i<n)
    {
        if(adLists[j]!= NULL)
        {
            cout<<j<<": "<<dfn[j]<<";"<<endl;
            i++;
        }
        j++;
    }
    
}
void Graph::Outputlow()
{
    int i = 0;
    int j = 0;
    while(i<n)
    {
        if(adLists[j]!= NULL)
        {
            cout<<j<<": "<<low[j]<<";"<<endl;
            i++;
        }
        j++;
    }
    
}
int main()
{
    cout<<"Demo of d1: "<<endl;
    Graph g1(8);
    g1.InsertVertex(0);
    g1.InsertVertex(1);
    g1.InsertVertex(2);
    g1.InsertVertex(3);
    g1.InsertVertex(4);
    g1.InsertVertex(5);
    g1.InsertVertex(6);
    g1.InsertVertex(7);
    g1.InsertEdge(0,2);
    g1.InsertEdge(0,1);
    g1.InsertEdge(2,3);
    g1.InsertEdge(1,3);
    g1.InsertEdge(4,5);
    g1.InsertEdge(5,6);
    g1.InsertEdge(6,7);
    cout<<"BFS: "<<endl;
    g1.BFS(0);
    cout<<endl;
    g1.BFS(3);
    cout<<endl;
    g1.BFS(7);
    cout<<endl;
    cout<<"DFS: "<<endl;
    g1.DFS(0);
    cout<<endl;
    g1.DFS(3);
    cout<<endl;
    g1.DFS(7);
    cout<<endl;
    cout<<"Components: "<<endl;
    g1.Components();
    cout<<"Dfnlow(3) "<<endl;
    g1.DfnLow(3);
    cout<<"Demo of d2: "<<endl;
    Graph g2(10);
    g2.InsertVertex(0);
    g2.InsertVertex(1);
    g2.InsertVertex(2);
    g2.InsertVertex(3);
    g2.InsertVertex(4);
    g2.InsertVertex(5);
    g2.InsertVertex(6);
    g2.InsertVertex(7);
    g2.InsertEdge(0,1);
    g2.InsertEdge(0,2);
    g2.InsertEdge(1,3);
    g2.InsertEdge(1,4);
    g2.InsertEdge(2,5);
    g2.InsertEdge(2,6);
    g2.InsertEdge(3,7);
    g2.InsertEdge(4,7);
    g2.InsertEdge(5,7);
    g2.InsertEdge(6,7);
    cout<<"BFS: "<<endl;
    g2.BFS(0);
    cout<<endl;
    g2.BFS(3);
    cout<<endl;
    g2.BFS(7);
    cout<<endl;
    cout<<"DFS: "<<endl;
    g2.DFS(0);
    cout<<endl;
    g2.DFS(3);
    cout<<endl;
    g2.DFS(7);
    cout<<endl;
    cout<<"Components: "<<endl;
    g2.Components();
    //cout<<endl;
    cout<<"Dfnlow(3) "<<endl;
    g2.DfnLow(3);
    cout<<"Demo of d3: "<<endl;
    Graph g3(10);
    g3.InsertVertex(0);
    g3.InsertVertex(1);
    g3.InsertVertex(2);
    g3.InsertVertex(3);
    g3.InsertVertex(4);
    g3.InsertVertex(5);
    g3.InsertVertex(6);
    g3.InsertVertex(7);
    g3.InsertVertex(8);
    g3.InsertVertex(9);
    g3.InsertEdge(0,1);
    g3.InsertEdge(1,2);
    g3.InsertEdge(1,3);
    g3.InsertEdge(2,4);
    g3.InsertEdge(3,4);
    g3.InsertEdge(3,5);
    g3.InsertEdge(5,6);
    g3.InsertEdge(5,7);
    g3.InsertEdge(6,7);
    g3.InsertEdge(7,8);
    g3.InsertEdge(7,9);
    cout<<"BFS: "<<endl;
    g3.BFS(0);
    cout<<endl;
    g3.BFS(3);
    cout<<endl;
    g3.BFS(7);
    cout<<endl;
    cout<<"DFS: "<<endl;
    g3.DFS(0);
    cout<<endl;
    g3.DFS(3);
    cout<<endl;
    g3.DFS(7);
    cout<<endl;
    cout<<"Components: "<<endl;
    g3.Components();
    //cout<<endl;
    cout<<"Dfnlow(3) "<<endl;
    g3.DfnLow(3);
    /*g1.BFS(0);
    cout<<endl;
    g1.DfnLow(0);
    g1.Components();*/
}