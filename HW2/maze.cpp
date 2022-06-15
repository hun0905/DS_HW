#include<iostream>
#include<stack>
#include <fstream>
using namespace std;
const int directa[8] = {-1,-1,0,1,1,1,0,-1};
const int directb[8] = {0,1,1,1,0,-1,-1,-1};
enum directions{N,NE,E,SE,S,SW,W,NW};
//int endx = 8,endy = 8;
int **maze;
int **mark;


struct Items{
    public:
        int x,y,dir;
        Items(int a = 0,int b = 0,int c = E):x(a),y(b),dir(c){}
        friend ostream& operator<<(ostream& os , Items & item);

};
string Outdir(int i)
{
    switch(i)
    {
        case N:
            return "N";
        case NE:
            return "NE";
        case E:
            return "E";
        case SE:
            return "SE";
        case S:
            return "S";
        case SW:
            return "SW";
        case W:
            return "W";
        default:
            return "NW";
        
    }
}
ostream& operator<<(ostream& os , Items & item)
{
    return os<<item.x+1<<","<<item.y+1<<","<<Outdir(item.dir);
}

template <class T>
void ChangeSize1D(T*&a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be > 0";
    T *temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}
template <class T>
class Bag
{
public:
    Bag(int bagCapacity = 10);
    virtual ~Bag();

    virtual int Size() const;
    virtual bool IsEmpty() const;
    virtual T &Element() const;

    virtual void Push(const T &);
    virtual void Pop();

protected:
    int capacity;
public:
    int top;
    T *array;
};

template <class T>
Bag<T>::Bag(int bagCaacity) : capacity(bagCaacity)
{
    if (capacity < 1)
        throw "capacity must be > 0";
    array = new T[capacity];
    top = -1;
}
template <class T>
Bag<T>::~Bag() { delete[] array; }
template<class T>
inline bool Bag<T>::IsEmpty()const{return Size()==0;}
template<class T>
inline int Bag<T>::Size() const {return top+1;}
template<class T>
inline T &Bag<T>::Element() const{
    if(IsEmpty())throw"Bag is empty";
    return array[0];
}
template <class T>
void Bag<T>::Push(const T &x)
{
    if (capacity == top + 1)
    {
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}
template <class T>
void Bag<T>::Pop()
{
    if (IsEmpty())
        throw "Bag is empty,cannot delete";
    int deletePos = top / 2;
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}
template <class T>
class Stack : public Bag<T>
{
public:
    Stack(int stackCapacity = 10);
    ~Stack();
    T &Top() const;
    void Pop();
    template<class U>
    friend ostream& operator<<(ostream& os,Stack<T>&s);
};

template <class T>
Stack<T>::Stack(int stackCapacity) : Bag<T>(stackCapacity) {}

template <class T>
Stack<T>::~Stack() {}

template <class T>
T &Stack<T>::Top() const
{
    if (this->IsEmpty())
        throw "stack is empty";
    return this->array[this->top];
}
template <class T>
void Stack<T>::Pop()
{
    
    if (this->IsEmpty())
        throw "stack is empty,Cannot delete.";
    this->top--;
}
template<class U>
ostream& operator<<(ostream& os,Stack<U>&s)
{
    //os<<"top ="<<s.top<<endl;
    for(int i = 0 ; i <= s.top ; i++)
    {
        os<<i<<": "<<s.array[i]<<endl;//
    }
    return os;
}

/*
bool findPath(int x , int y)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        //mark[x][y] =1;
        x += directa[i];
        y += directb[i];
        if(x == endx && y == endy )
        {
            
            return true;
        }
        if( (!maze[x][y]) && (!mark[x][y]) )   findPath(x,y);
    }
    return false;
}*/
void Path(const int m, const int p)
{
    
    mark[0][0]=1;
    Stack<Items>stack;
    Items temp(0,0,N);
    stack.Push(temp);
    while(!stack.IsEmpty())
    {
        temp = stack.Top();
        stack.Pop();
        int i = temp.x;int j = temp.y;int d = temp.dir;
        while(d<8)
        {
            while(i+directa[d] >  m|| j+directb[d] >  p|| i+directa[d] < 0 || j+directb[d] < 0)
                d++;
            int g = i +directa[d];int h = j + directb[d];
            if((g == m) && (h==p))
            {
                
                cout<<stack;
                cout<<stack.top+1<<": "<<i+1<<","<<j+1<<","<<Outdir(d)<<endl;
                cout<<stack.top+2<<": "<<m+1<<","<<p+1<<endl;
                
                return;
            }
            if( (!maze[g][h]) && (!mark[g][h]))
            {
                mark[g][h]=1;
                temp.x=i;temp.y=j;temp.dir=d;
                stack.Push(temp);
                i=g;j=h;d=N;
            }
            else d++;
        }
    }
    cout<<"No path in maze"<<endl;
}


int main()
{
    fstream file;
    file.open("Matrix3_11.txt",ios::in);
    int row,col;
    cout<<"input row of maze: ";
    cin>>row;
    cout<<"input column of maze: ";
    cin>>col;
    cout<<"read maze 3.11"<<endl;
    maze = new int*[row];
    mark = new int*[row];
    for(int i = 0 ; i < row ; i++)
    {
        maze[i] = new int[col];
        mark[i] = new int[col];
    }
    
    for(int i = 0 ; i < row ; i++)
    {
        for(int j =0 ; j < col ; j++)
        {
            char tmp;
            file.get(tmp);
            while(tmp < 48 || tmp > 57)
                file.get(tmp);
            maze[i][j] = tmp - 48;
        }
    }   
    cout<<"maze in 3.11"<<endl;
    Path(row-1,col-1);    
}