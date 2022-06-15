#include<iostream>
#include <math.h>
using namespace std;
struct Term{
    double coef;
    int exp;
    Term Set(int c, int e){coef = c;exp = e;return *this;}
};

template<class T> class CircularList;
template<class T>
class Node
{
friend class CircularList<T>;
private:
    T data;
    Node<T>*link;
};
template<class T>
class CircularList
{
public:
    template<class U>
    friend ostream& operator<<(ostream &os, CircularList<T> &L);
    CircularList(){head = GetNode();head->link = head;last = head;}
    ~CircularList();
    void InsertFront(T e);
    void InsertHead(T e);
    void Insert(int i, T e);
    void DeleteFront();
    void DeleteBack();
    void Delete(int i = 0);
	void RetNode(Node<T>*&x);
    void DeleteList();
	Node<T>* GetNode();
    T Head() const;
    T Front() const;
    T Back() const;
    T Get(int i = 0) const;
    bool IsEmpty(int i);
private:
    Node<T>*head;
	Node<T>*last;
	inline static Node<T>* av;
};
template<class T>
Node<T>* CircularList<T>::GetNode()
{
	Node<T>*x;
	if(av)
	{
		x = av;
		av = av->link;
	}
	else 
	{
		x = new Node<T>;
	}
	return x;
}
template<class T>
void CircularList<T>::RetNode(Node<T>*&x)
{
	x->link = av;
	av = x;
	x = 0;	
}
template<class T>
void CircularList<T>::InsertHead(T e)
{
    head->data = e;
}
template<class T>
void CircularList<T>::InsertFront(T e)
{   
    Node<T>* n = GetNode();
    n->data = e;
	if(head->link == head)
		last = n;
    n->link = head->link;
    head->link = n;
    
    n = 0;
}
template<class T>
void CircularList<T>::Insert(int i , T e)
{
    Node<T>* NEW = GetNode();
    NEW->data = e;
    if(i == 0)
    {
        NEW->link = head->link;
        if(head->link == head)
			last = NEW;
		head->link = NEW;
    }
    int count = 0;
    for(Node<T>* n = head->link; n != head;n = n->link  )
    {
        if(count == i-1)
        {
            if(n->link == head)
				last = NEW;
			NEW->link = n->link;
            n->link = NEW;         
        }
        count++;
    }
    NEW = 0;  
}
template<class T>
void CircularList<T>::DeleteFront()
{
    Node<T>*tmp = head->link;
    if(head->link != head)
    {
        if(head->link->link == head)
			last = 0;
		head->link = head->link->link;
        delete tmp;
    }
}
template<class T>
void CircularList<T>::DeleteBack() 
{
    for(Node<T>* n = head;n->link != head;  n = n->link )
    {
        if(n->link->link == head)
        {
            RetNode(n->link);
            n->link = head;
			last = n;
        }
    }
}
template<class T>
void CircularList<T>::Delete(int i)
{
    if(i == 0 )
    {
        Node<T>* tmp = head->link;
		if(head->link->link == head)
			last = 0;
        head->link = head->link->link;
        if(tmp!= head)RetNode(tmp);
        return;
    }
    int count = 0;
    for(Node<T>* n = head->link; n != head ;n = n->link )
    {
        if(count == i-1)
        {
            Node<T>* tmp = n->link;
			if(n->link->link == head)
				last = n;
            n->link = n->link->link;
            if(tmp != head)RetNode(tmp);
        }
        count++;
    }  
}
template<class T>
T CircularList<T>::Head() const
{
    return head->data;    
}
template<class T>
T CircularList<T>::Front() const
{
    return head->link->data;    
}
template<class T>
T CircularList<T>::Back() const
{
    for(Node<T>* n = head->link;n != head  ; n = n->link)
    {
        if(n->link == head)
            return n->data;
    }  
}
template<class T>
T CircularList<T>::Get(int i) const
{
    int count = 0;
    for(Node<T>* n = head->link; n != head;n = n->link )
    {
        if(count == i)
            return n->data;
        count++;
    }  
    return head->data;
}
template<class T>
bool CircularList<T>::IsEmpty(int i)
{
    int count = 0;
    for(Node<T>*n= head->link; n != head ; n=n->link)
    {
        if(count == i&& n != head )  
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
ostream &operator<<(ostream &os, CircularList<U> &L) 
{
    int count = 0;
    while(!L.IsEmpty(count))
    {
        os<<L.Get(count);
        count++;
        if(!L.IsEmpty(count))cout<<" "; 
    }
}

template<class T>
CircularList<T> ::~CircularList()
{
    if(last)
    {
        Node<T>*x = last->link;
        last->link = av;
        av = x;
        last = 0;
        x = 0;
    }
    
}
template<class T>
void CircularList<T>::DeleteList()
{
    if(last)
    {
        Node<T>*x = last->link;
        last->link = av;
        av = x;
        last = 0;
    }
}
class Polynomial
{
public:
    friend class CircularList<Term>;
    friend istream& operator>>(istream &is, Polynomial &L);
    friend ostream& operator<<(ostream &is, Polynomial &L) ;
    Polynomial(const Polynomial &a ){*this = a;}
    Polynomial(){}
    ~Polynomial(){
        poly.DeleteList();
    }
    const Polynomial& operator=( const Polynomial &a);
    Polynomial operator+( const Polynomial &b) const;
    Polynomial operator-( const Polynomial &b) const;
    Polynomial operator*( const Polynomial &b) const;
    double evaluate(double number) const;
private:
    CircularList<Term>poly;
};
double Polynomial::evaluate(double number) const
{
    double sum=0;
    for(int i = poly.Head().coef-1; i>=0 ; i--)
    {
        sum+=poly.Get(i).coef*pow(number,poly.Get(i).exp);
    }
    return sum;
}
istream &operator>>(istream &is, Polynomial &L) 
{
    Term t;
    t.exp = 0;
    is>>t.coef;
    L.poly.InsertHead(t);
    for(int i = 0 ; i < t.coef ; i++)
    {
        Term *tmp = new Term;
        is>>tmp->coef;
        is>>tmp->exp;
        L.poly.InsertFront(*tmp);
    }
    return is;
}
const Polynomial& Polynomial::operator=( const Polynomial &a)
{
    Term t;
    poly.InsertHead(a.poly.Head());
    for(int i = a.poly.Head().coef-1; i>=0 ; i--)
    {
        poly.InsertFront( t.Set(a.poly.Get(i).coef,a.poly.Get(i).exp) );
    }
}
Polynomial Polynomial::operator+( const Polynomial &b) const
{
    Polynomial c;
    int count = 0;

    int posa=poly.Head().coef-1,posb = b.poly.Head().coef-1;
    
    Term tmp,h;
    while(posa >= 0 && posb >= 0)
    {
        count++;
        if(poly.Get(posa).exp == b.poly.Get(posb).exp)
        {
            int sum = poly.Get(posa).coef + b.poly.Get(posb).coef;
            if(sum==0)count--;
            if(sum) c.poly.InsertFront(tmp.Set(sum,poly.Get(posa).exp));
            posa--;posb--;
        }
        else if(poly.Get(posa).exp < b.poly.Get(posb).exp)
        { 
             c.poly.InsertFront(tmp.Set(b.poly.Get(posb).coef,b.poly.Get(posb).exp));
             posb--;
        }
        else
        {
            c.poly.InsertFront(tmp.Set(poly.Get(posa).coef,poly.Get(posa).exp));
            posa--;
        }
        
    }
    
    while(posa >= 0)
    {c.poly.InsertFront(tmp.Set(poly.Get(posa).coef,poly.Get(posa).exp));posa--; count++;}
    while(posb>=0)
    {c.poly.InsertFront(tmp.Set(b.poly.Get(posb).coef,b.poly.Get(posb).exp));posb--;count++;}
    h.coef =  count;
    c.poly.InsertHead(h);
    return c;
}
Polynomial Polynomial::operator-( const Polynomial &b) const
{
    Polynomial c;
    int count = 0;

    int posa=poly.Head().coef-1,posb = b.poly.Head().coef-1;
    
    Term tmp,h;
    while(posa >= 0 && posb >= 0)
    {
        count++;
        if(poly.Get(posa).exp == b.poly.Get(posb).exp)
        {
            int sum = poly.Get(posa).coef - b.poly.Get(posb).coef;
            if(sum == 0)count--;
            if(sum) c.poly.InsertFront(tmp.Set(sum,poly.Get(posa).exp));
            posa--;posb--;
        }
        else if(poly.Get(posa).exp < b.poly.Get(posa).exp)
        { 
             c.poly.InsertFront(tmp.Set(b.poly.Get(posb).coef,b.poly.Get(posb).exp));
             posb--;
        }
        else
        {
            c.poly.InsertFront(tmp.Set(poly.Get(posa).coef,poly.Get(posa).exp));
            posa--;
        }
        
    }
    while(posa >= 0)
    {c.poly.InsertFront(tmp.Set(poly.Get(posa).coef,poly.Get(posa).exp));posa--; count++;}
    while(posb>=0)
    {c.poly.InsertFront(tmp.Set(b.poly.Get(posb).coef,b.poly.Get(posb).exp));posb--;count++;}
    h.coef =  count;
    c.poly.InsertHead(h);
    return c;
}
Polynomial Polynomial::operator*( const Polynomial &b) const 
{
    Polynomial c;
    Term t,h;
    h.coef = 0;
    c.poly.InsertHead(h);
    h.coef =  b.poly.Head().coef;
    
    for(int i =  poly.Head().coef-1 ; i >=0 ; i--)
    {
        Polynomial  tmp;
        for(int j = b.poly.Head().coef-1 ; j>= 0 ; j--)
        {
            tmp.poly.InsertFront( t.Set(poly.Get(i).coef * b.poly.Get(j).coef, poly.Get(i).exp+b.poly.Get(j).exp) );
        }
        tmp.poly.InsertHead(h);
        if(i ==  poly.Head().coef-1)
            c = tmp;
        else
            c = c + tmp;
    }
    return c;
}
ostream &operator<<(ostream &os, Polynomial &L)  
{
    for(int i = L.poly.Head().coef-1 ; i >= 0;i--)
    {
        if(i != L.poly.Head().coef-1 )
            os<<"+";
        os<<L.poly.Get(i).coef;
        if(L.poly.Get(i).exp != 0)
            os<<"x^"<<L.poly.Get(i).exp;
    }
    return os;
}

int main()
{
    Polynomial a,b;
    cout<<"input a(高次到低次)"<<endl;
    cin>>a;
    cout<<"output a"<<endl;
    cout<<a;
    cout<<endl;
    cout<<"copy a to c by Polynomial(const Polynomial& a)"<<endl;
    Polynomial c(a);
    cout<<"output c"<<endl;
    cout<<c;
    cout<<endl;
    cout<<"assign a to d by ="<<endl;
    Polynomial d;
    d = a;
    cout<<"output d"<<endl;
    cout<<d;
    cout<<endl;
    cout<<"input b"<<endl;
    cin>>b;
    cout<<"output b"<<endl;
    cout<<b;
    cout<<endl;
    Polynomial ans;
    cout<<"output a+b"<<endl;
    ans =a+b;
    cout<<ans;
    cout<<endl;
    cout<<"output a-b"<<endl;
    ans =a-b;
    cout<<ans;
    cout<<endl;
    cout<<"output a*b"<<endl;
    ans =a*b;
    cout<<ans;
    cout<<endl;
    cout<<"output a.evaluate(2.5)"<<endl;
    cout<<a.evaluate(2.5);
    cout<<endl;
    /*Polynomial p,q;
    double n;
    cin>>p;
    cout<<p<<endl;
    cin>>n;
    cout<<p.evaluate(n)<<endl;*/
    
}