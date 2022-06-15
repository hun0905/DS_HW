#include<iostream>
using namespace std;


class LinearProbing{
    public:
        LinearProbing(){
            ht = new string*[26];
            size = 0;
            max = 26;
            /*for(int i = 0 ; i < 26 ; i++)
            {
                ht[i] = new string;
            }*/
        }
        string* Search(const string& k);
        void Insert(const string& k);
        void Display()
        {
            for(int i = 0 ; i < 26 ; i++)
            {
                cout<<"ht["<<i<<"]: ";
                if(ht[i] != NULL)
                    cout<<*ht[i]<<" ";
                cout<<endl;
            }
        }
    private:
        string **ht;//key
        int size;
        int max;
        int h(string k){
            if(k[0] >= 97)
                return k[0]-97;
            else
                return k[0]-65;
        }
};

string* LinearProbing::Search(const string& k)
{
    int i = h(k);
    int j;
    for(j = i ; ht[j] && *ht[j] != k;){
        j = (j+1)%max;
        if(j == i)return 0;
    }
    if(*ht[j] == k) return ht[j];
    return 0;
}
void LinearProbing::Insert(const string& k)
{
    int i = h(k);
    int j;
    for(j = i ; ht[j];)
    {
        j = (j+1)%max;
    }
    ht[j] = new string; 
    *ht[j] = k; 
    size++;
}
class Chaining;
class ChainNode{
    friend Chaining;
    string data;
    ChainNode*link;
};
class Chaining{
    public:
        Chaining(){
            ht = new ChainNode*[26];
            for(int i = 0 ; i < 26 ; i++)
                ht[i] = new ChainNode;    
            size = 0;
        }
        string* Search(const string& k);
        void Insert(const string& k);
        void Display();
    private:
        ChainNode **ht;
        int size;
        int h(string k){
            if(k[0] >= 97)
                return k[0]-97;
            else
                return k[0]-65;
        }
};
void Chaining::Display()
{
    for(int i = 0 ; i <  26 ; i++)
    {
        cout<<i;
        for(ChainNode*n = ht[i]->link ; n ; n = n->link)
        {
            cout<<"->"<<n->data;
        }
        cout<<endl;
    }
}
string* Chaining::Search(const string& k)
{
    int i = h(k);
    for(ChainNode *current = ht[i];current;current=current->link)
    {
        if(current->data == k)return &current->data;
    }
    return 0;
}
void Chaining::Insert(const string& k)
{
    int i = h(k);
    for(ChainNode *current = ht[i];current;current=current->link)
    {
        if(current->link == NULL)
        {
            ChainNode*tmp = new ChainNode;
            tmp->data = k;
            current->link = tmp;
            return;
        }
    }
    return;
}
int main()
{
    LinearProbing a;
    cout<<"Setup and Insert 12 keys objects:GA,D,A,G,L,A2,A1,A3,A4,Z,ZA,E"<<endl;
    a.Insert("GA");
    a.Insert("D");
    a.Insert("A");
    a.Insert("G");
    a.Insert("L");
    a.Insert("A2");
    a.Insert("A1");
    a.Insert("A3");
    a.Insert("A4");
    a.Insert("Z");
    a.Insert("ZA");
    a.Insert("E");
    cout<<"Display: "<<endl;
    a.Display();
    cout<<"Search(\"GA\"): "<<"address:"<<a.Search("GA")<<", key: "<<*a.Search("GA")<<endl;
    cout<<"Search(\"A\"): "<<"address:"<<a.Search("A")<<", key: "<<*a.Search("A")<<endl;
    cout<<"Search(\"A2\"): "<<"address:"<<a.Search("A2")<<", key: "<<*a.Search("A2")<<endl;
    cout<<"Search(\"ZA\"): "<<"address:"<<a.Search("ZA")<<", key: "<<*a.Search("ZA")<<endl;
    cout<<"Search(\"E\"): "<<"address:"<<a.Search("E")<<", key: "<<*a.Search("E")<<endl;
    cout<<endl;
    Chaining b;
    cout<<"Setup and Insert 12 keys objects:A4,D,E,G,L,ZA,A3,GA,Z,A1,A2,A"<<endl;
    b.Insert("A4");
    b.Insert("D");
    b.Insert("E");
    b.Insert("G");
    b.Insert("L");
    b.Insert("ZA");
    b.Insert("A3");
    b.Insert("GA");
    b.Insert("Z");
    b.Insert("A1");
    b.Insert("A2");
    b.Insert("A");
    cout<<"Display: "<<endl;
    b.Display();
    cout<<"Search(\"A4\"): "<<"address:"<<b.Search("A4")<<", key: "<<*b.Search("A4")<<endl;
    cout<<"Search(\"G\"): "<<"address:"<<b.Search("G")<<", key: "<<*b.Search("G")<<endl;
    cout<<"Search(\"ZA\"): "<<"address:"<<b.Search("ZA")<<", key: "<<*b.Search("ZA")<<endl;
    cout<<"Search(\"GA\"): "<<"address:"<<b.Search("GA")<<", key: "<<*b.Search("GA")<<endl;
    cout<<"Search(\"A\"): "<<"address:"<<b.Search("A")<<", key: "<<*b.Search("A")<<endl;
    
}