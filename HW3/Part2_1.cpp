#include<iostream>
using namespace std;
template<class T> class List;
template<class T>
class Node
{
friend class List<T>;
private:
    T data;
    Node<T>*link;
};
template<class T>
class List
{
public:
    template<class U>
    friend ostream& operator<<(ostream &os, List<T> &L);
    List(){first = 0;}
    ~List();
    void InsertFront(T e);
    void Insert(int i, T e);
    void DeleteFront();
    void DeleteBack();
    void Delete(int i = 0);
    T Front();
    T Back();
    T Get(int i = 0);
    bool IsEmpty(int i);
    class Iterator
    {
    public:
        Iterator(Node<T>* startNode = 0)
        {current = startNode;}
        T &operator *() const{return current->data;}
        T* operator ->() const{return &current->data;}
        Iterator& operator ++(){current = current->link;return *this;}
        Iterator& operator ++(int)
        {
            Iterator old = *this;
            current = current ->link;
            return old;
        }
        bool operator !=(const Iterator r)
        {return current != r.current;}
        bool operator ==(const Iterator r)
        {return current == r.current;}
    private:
        Node<T>* current;
    };
    Iterator begin()
        {return Iterator(first);}
    Iterator end()
        {return Iterator(0);}
private:
    Node<T> * first;
};

template<class T>
void List<T>::InsertFront(T e)
{   
    Node<T>* n = new Node<T>;
    n->data = e;
    if(first == 0)
        first = n;    
    else
    {
        n->link = first;
        first = n;
    }
    n = 0;
}
template<class T>
void List<T>::Insert(int i , T e)
{
    Node<T>* NEW = new Node<T>;
    NEW->data = e;
    if(i == 0)
    {
        NEW->link = first;
        first = NEW;
    }
    int count = 0;
    for(Node<T>* n = first; n != 0;n = n->link  )
    {
        if(count == i-1)
        {
            NEW->link = n->link;
            n->link = NEW;         
        }
        count++;
    }
    NEW = 0;  
}
template<class T>
void List<T>::DeleteFront()
{
    Node<T>*tmp = first;
    if(first->link != 0)
        first = first->link;
    delete tmp;
}
template<class T>
void List<T>::DeleteBack() 
{
    for(Node<T>* n = first;n != 0;  n = n->link )
    {
        if(n->link->link == 0)
        {
            delete n->link;
            n->link = 0;
        }
    }
}
template<class T>
void List<T>::Delete(int i)
{
    if(i == 0)
    {
        Node<T>* tmp = first;
        first = first->link;
        delete tmp;
        return;
    }
    int count = 0;
    for(Node<T>* n = first; n != 0 ;n = n->link )
    {
        if(count == i-1)
        {
            Node<T>* tmp = n->link;
            n->link = n->link->link;
            delete tmp;
        }
        count++;
    }  
}
template<class T>
T List<T>::Front()
{
    return first->data;    
}
template<class T>
T List<T>::Back()
{
    for(Node<T>* n = first;n != 0  ; n = n->link)
    {
        if(n->link == 0)
            return n->data;
    }  
}
template<class T>
T List<T>::Get(int i)
{
    int count = 0;
    for(Node<T>* n = first; n != 0;n = n->link )
    {
        if(count == i)
            return n->data;
        count++;
    }  
    return first->data;
}
template<class T>
bool List<T>::IsEmpty(int i)
{
    int count = 0;
    for(Node<T>*n= first; n != 0 ; n=n->link)
    {
        if(count == i&& n != 0 )  
        {
            n = 0;
            return false;
        }
        if(count > i)   break;
        count++;
    }
    return true;
}
template<class U>
ostream &operator<<(ostream &os, List<U> &L) 
{
    int count = 0;
    while(!L.IsEmpty(count))
    {
        os<<L.Get(count);
        count++;
        if(!L.IsEmpty(count))cout<<" "; 
    }
    cout<<endl;
}
template<class T>
List<T> ::~List()
{
    for(Node<T>* n = first; n != 0;)
    {
        Node<T>* tmp = n;
        n = n->link;
        delete tmp;
    }
}
int main()
{
    List<int>L;
    cout<<"construct a list L"<<endl;
    L.InsertFront(4);
    L.InsertFront(2);
    L.InsertFront(0);
    cout<<"InsertFront 4"<<endl;
    cout<<"InsertFront 2"<<endl;
    cout<<"InsertFront 0"<<endl;
    cout<<"Output L: ";
    cout<<L;
    cout<<"Delete Front"<<endl;
    L.DeleteFront();
    cout<<"Output L: ";
    cout<<L;
    cout<<"Delete Back"<<endl;
    L.DeleteBack();
    cout<<"Output L: ";
    cout<<L;
    cout<<"InsertFront 4"<<endl;
    cout<<"InsertFront 6"<<endl;
    L.InsertFront(4);
    L.InsertFront(6);
    cout<<"Output L: ";
    cout<<L;
    cout<<"Output L Front: ";
    cout<<L.Front();
    cout<<endl;
    cout<<"Output L Back: ";
    cout<<L.Back();
    cout<<endl;
    cout<<"Output L.Get(1): ";
    cout<<L.Get(1) ;
    cout<<endl;
    cout<<"L.Delete(1)"<<endl;
    L.Delete(1) ;
    cout<<"Output L: ";
    cout<<L;
    cout<<"L.Insert(1,4) "<<endl;
    L.Insert(1,4) ;
    cout<<"Output L: ";
    cout<<L;
    cout<<"Output L by Iterator: ";
    for(List<int>::Iterator i = L.begin();i!=L.end();i++)   
    {
        cout<<*i<<" ";
    }
    cout<<endl;
}