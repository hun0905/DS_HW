#include<iostream>

#include <iomanip>
using namespace std;
#define infinite 1000000000
class Graph;
class Node
{
    friend class Graph;
    private:
        bool exist;
        int data;
};

class Graph
{
    public:
        ~Graph(){}
        Graph(int NumOfNode = 10){
            n = NumOfNode;
            e = 0;
            admatrix = new Node*[NumOfNode];
            income = new int[NumOfNode];
            for(int i = 0 ; i < NumOfNode ; i++)
            {
                income[i] = 0;
                admatrix[i] = new Node[NumOfNode];
                for(int j = 0 ; j < NumOfNode ; j++) 
                {  
                    admatrix[i][j].exist = false;
                    admatrix[i][j].data = infinite;
                }
            }
        }
        bool IsEMpty() const{return n == 0 ;}
        int NumberOfVertices()const{return n;}
        int NumberOfEdges() const {return e;}
        bool ExistEdge(int u, int v) const{return admatrix[u][v].exist;};
        void InsertEdge(int u,int v,int w);
        void DeleteEdge(int u,int v);
        void ShortestPath(const int n , const int v);
        void BellmanFord(const int n,const int v);
        void AllLengths(const int n);
        void OutPutMatrix()
        {
            for(int i = 0 ; i < n ; i++)
            {
                for(int j = 0 ; j < n ; j++)
                    if(admatrix[i][j].exist == true)
                        cout<<admatrix[i][j].data;
                cout<<endl;
            }
        }
    private:
        Node **admatrix;
        int n;
        int e;
        int *income;
};


void Graph::InsertEdge(int u,int v,int w)
{
    admatrix[u][v].data = w;
    admatrix[u][v].exist = true;
    e++;
    income[v]++;
}
void Graph::DeleteEdge(int u,int v)
{
    admatrix[u][v].data = 0;
    admatrix[u][v].exist = false; 
    e--;
}
void Graph::ShortestPath(const int n , const int v)
{
    cout<<setw(7)<<"Vertex";
    for(int i = 0 ; i < n ; i++)
    {
        cout<<setw(7)<<i;
    }
    cout<<endl;
    bool s[n];
    int dist[n];
    string path[n];
    for(int i = 0 ; i <n ; i++){s[i] = false;dist[i] = admatrix[v][i].data;}
    s[v]= true;
    dist[v] = 0;
    cout<<"Initial";
    for(int i = 0 ; i < n ; i++)
    {
        path[i]=to_string(v)+",";
        if(dist[i] > 99999999)
            cout<<setw(7)<<"INF";
        else
            cout<<setw(7)<<dist[i];
    }
    cout<<endl;
    int count = 1;
    bool first = true;
    for(int i = 0 ; i < n-2 ; i++){
        bool f =true;
        int u  = 0;
        for(int j = 0 ; j < n ; j++)
        {
            if(s[j] == false&& (dist[j] < dist[u] ||f)  )
            {
                u = j;
                f = false;
            }
        }
        s[u] = true;
        for(int w = 0 ; w < n ; w++)
        {
            if(!s[w]&&dist[u]+admatrix[u][w].data<dist[w] && admatrix[u][w].exist)
            {
                dist[w] = dist[u] + admatrix[u][w].data; 
                path[w] = path[u]+to_string(u)+",";
            }
        }
        cout<<setw(7)<<count;
        for(int i = 0 ; i < n ; i++)
        {
            if(dist[i] > 99999999)
                cout<<setw(7)<<"INF";
            else
                cout<<setw(7)<<dist[i];
        }
        cout<<endl;
        count++;
    }
    for(int i  = 0 ; i < n ; i++)
    {
        if(dist[i]<999999)
            if(i != v)
                cout<<"shortest path from "<<v<<" to "<<i<<": "<<path[i]<<i<<endl;
            else
                cout<<"shortest path from "<<v<<" to "<<i<<": "<<i<<endl;
    }
}
void Graph::BellmanFord(const int n,const int v)
{
    int dist[n];
    int count = 1;
    for(int i = 0 ; i < n ; i++)dist[i] = admatrix[v][i].data;

    cout<<setw(7)<<"k";
    for(int i = 0 ; i < n ; i++)
    {
        cout<<setw(7)<<i;
    }
    cout<<endl;
    dist[v] = 0;
    cout<<setw(7)<<count;
    count++;
    for(int i = 0 ; i < n ; i++)
    {
        if(dist[i] > 99999999)
            cout<<setw(7)<<"INF";
        else
            cout<<setw(7)<<dist[i];
    }
    cout<<endl;
    for(int k = 2 ; k <= n-1 ; k++)
    {
        
        int tmp[n];
        for(int i = 0 ;  i< n ; i++)
            tmp[i] =dist[i];
        for(int u = 0 ; u < n ; u++)
        {
            if(income[u] > 0 && u != v) 
            { 
                
                for(int i = 0 ; i < n; i++)
                {
                    if(dist[u] > tmp[i]+admatrix[i][u].data && admatrix[i][u].exist == true) 
                    {
                        dist[u] = tmp[i] + admatrix[i][u].data;
                    }
                }
                
            }
        }
        cout<<setw(7)<<count;
        count++;
        for(int i = 0 ; i < n ; i++)
        {
            if(dist[i] > 99999999)
                cout<<setw(7)<<"INF";
            else
                cout<<setw(7)<<dist[i];
        }
        cout<<endl;
    }
    
}
void Graph::AllLengths(const int n)
{
    int a[n][n];
    int count = -1;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j <  n ; j++)
        {
            if(i!=j)
                a[i][j] = admatrix[i][j].data;
            else
                a[i][j]= 0;
        }
    cout<<"A"<<count<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            if(a[i][j]>9999999 )
                cout<<setw(5)<<"INF";
            else
                cout<<setw(5)<<a[i][j];
        cout<<endl;
    }
    cout<<endl;
    count++;
    for(int k = 0 ; k < n ; k++)
    {
        
        for(int i = 0 ;  i < n ; i++)
            for(int j = 0  ; j < n ; j++)
                if(i == j) a[i][j] = 0;
                else if( (a[i][k]+a[k][j])<a[i][j]) a[i][j] = a[i][k]+a[k][j];
        cout<<"A"<<count<<endl;
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++)
                if(a[i][j]>9999999 )
                    cout<<setw(5)<<"INF";
                else
                    cout<<setw(5)<<a[i][j];
            cout<<endl;
        }
        cout<<endl;
        count++;
    }
    
}
int main()
{
    Graph g1_1(8);
    g1_1.InsertEdge(1,0,300);
    g1_1.InsertEdge(2,1,800);
    g1_1.InsertEdge(2,0,1000);
    g1_1.InsertEdge(3,2,1200);
    g1_1.InsertEdge(4,3,1500);
    g1_1.InsertEdge(4,5,250);
    g1_1.InsertEdge(5,3,1000);
    g1_1.InsertEdge(7,0,1700);
    g1_1.InsertEdge(5,7,1400);
    g1_1.InsertEdge(5,6,900);
    g1_1.InsertEdge(6,7,1000);
   
    cout<<"G1"<<endl;
    g1_1.ShortestPath(8,4);
    cout<<endl;
    Graph g1_2(6);
    g1_2.InsertEdge(0,1,50);
    g1_2.InsertEdge(1,2,10);
    g1_2.InsertEdge(0,2,45);
    g1_2.InsertEdge(0,3,10);
    g1_2.InsertEdge(3,0,20);
    g1_2.InsertEdge(1,3,15);
    g1_2.InsertEdge(3,4,15);
    g1_2.InsertEdge(4,1,20);
    g1_2.InsertEdge(4,2,35);
    g1_2.InsertEdge(2,4,30);
    g1_2.InsertEdge(5,4,3);
    cout<<"G1\' "<<endl;
    g1_2.ShortestPath(6,0);
    cout<<endl;

    Graph g1_3(10);
    g1_3.InsertEdge(0,1,20);
    g1_3.InsertEdge(0,2,15);
    g1_3.InsertEdge(1,0,2);
    g1_3.InsertEdge(1,4,10);
    g1_3.InsertEdge(1,5,30);
    g1_3.InsertEdge(2,3,4);
    g1_3.InsertEdge(2,5,10);
    g1_3.InsertEdge(4,3,15);
    g1_3.InsertEdge(5,4,10);
    g1_3.InsertEdge(5,3,4);
    cout<<"G1\" "<<endl;
    g1_3.ShortestPath(6,0);
    cout<<endl;
    Graph g2_1(7);
    g2_1.InsertEdge(0,1,6);
    g2_1.InsertEdge(0,2,5);
    g2_1.InsertEdge(0,3,5);
    g2_1.InsertEdge(1,4,-1);
    g2_1.InsertEdge(2,1,-2);
    g2_1.InsertEdge(2,4,1);
    g2_1.InsertEdge(3,2,-2);
    g2_1.InsertEdge(3,5,-1);
    g2_1.InsertEdge(4,6,3);
    g2_1.InsertEdge(5,6,3);
    cout<<"G2 "<<endl;
    g2_1.BellmanFord(7,0);
    cout<<endl;

    Graph g2_2(3);
    g2_2.InsertEdge(0,1,7);
    g2_2.InsertEdge(1,2,-5);
    g2_2.InsertEdge(0,2,5);
    cout<<"G2\' "<<endl;
    g2_2.BellmanFord(3,0);

    Graph g3_1(3);
    g3_1.InsertEdge(0,1,4);
    g3_1.InsertEdge(0,2,11);
    g3_1.InsertEdge(1,0,6);
    g3_1.InsertEdge(1,2,2);
    g3_1.InsertEdge(2,0,3);
    cout<<"G3 "<<endl;
    g3_1.AllLengths(3);
    cout<<endl;
    cout<<"G2 "<<endl;
    g2_1.AllLengths(7);
    
}