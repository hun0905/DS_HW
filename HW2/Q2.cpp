#include <iostream>
using namespace std;
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
    T *array;
    int capacity;
    int top;
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
template <class T>
class Queue : public Bag<T>
{
public:
    Queue(int queueCapacity = 10);
    T &Front() const;
    T &Rear() const;
    int Size();
    void Pop();
    void Push(const T& x);
    bool IsEmpty() const;
protected:
    int rear;
    int front;
};
template <class T>
Queue<T>::Queue(int queueCapacity )
{
    this->capacity = queueCapacity;
    if (this->capacity < 1)
        throw "Queue capacity must be > 0";
    this->array = new T[this->capacity];
    front = rear = 0;
}
template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

template<class T>
T& Queue<T>:: Front() const
{
    if(IsEmpty())throw "Queue is empty , No front element";
    return this->array[(front+1)% (this->capacity) ];
}


template<class T>
inline int Queue<T>::Size()
{
    
    if (rear % this->capacity > front % this->capacity)
        return rear % this->capacity - front % this->capacity;
    else
        return this->capacity - front % this->capacity + rear % this->capacity;
}
template <class T>
T& Queue<T>::Rear() const
{
    if( IsEmpty() ) throw"Queue is empty, Np rear element";
    return this->array[rear];
}
template<class T>
void Queue<T>::Push(const T& x)
{
    if((rear+1)%this->capacity == front)
    {
        T *newQu = new T[2*this->capacity];
        this->capacity*=2;
        int start = (front+1)%this->capacity;
        if(start < 2)
            copy(this->array+start, this->array+start+this->capacity-1,newQu);
        else{
            copy(this->array+start,this->array+this->capacity,newQu);
            copy(this->array,this->array+rear+1,newQu+this->capacity-start);
        }
        front = 2*this->capacity-1;
        rear = this->capacity-2;
        delete[] this->array;
        this->array = newQu;
    }
    rear = (rear+1)%this->capacity; this->array[rear] = x;
}
template<class T>
void Queue<T>::Pop()
{
    if(this->IsEmpty())throw"Queue is empty , cannot delete";
    front = (front+1) % this->capacity;
    this->array[front].~T();
}

template <class T>
class Deque : public Queue<T>
{
public:
    Deque(int DequeCapacity);
    void PopR();
    void PushF(const T& x);
};
template<class T>
Deque<T>::Deque(int DequeCapacity) : Queue<T>(DequeCapacity) {}

template<class T>
void Deque<T>::PushF(const T& x)
{
    if((this->rear+1)%this->capacity == this->front)
    {
        T *newQu = new T[2*this->capacity];
        this->capacity*=2;
        int start = (this->front+1)%this->capacity;
        if(start < 2)
            copy(this->array+start, this->array+start+this->capacity-1,newQu);
        else{
            copy(this->array+start,this->array+this->capacity,newQu);
            copy(this->array,this->array+this->rear+1,newQu+this->capacity-start);
        }
        this->front = 2*this->capacity-1;
        this->rear = this->capacity-1;
        delete[] this->array;
        this->array = newQu;
    }
    this->array[this->front%(this->capacity)] = x;
    this->front = (this->front+this->capacity-1)%this->capacity;
}
template<class T>
void Deque<T>::PopR()
{
    if(this->IsEmpty())throw"Queue is empty , cannot delete";
    
    this->array[this->rear].~T();
    this->rear = (this->rear-1)%this->capacity;
}


int main()
{
    cout<<"Demo for Deque(char)"<<endl;
    Deque<char>i(10);
    cout<<"Push [d, e, f] to rear"<<endl;
    i.Push('d');
    i.Push('e');
    i.Push('f');
    cout<<"size: "<<i.Size()<<endl;
    cout<<"Front: "<<i.Front()<<endl;
    cout<<"Rear: "<<i.Rear()<<endl;
    cout<<"Push [c, b, a] to front"<<endl;
    i.PushF('c');
    i.PushF('b');
    i.PushF('a');
    cout<<"size: "<<i.Size()<<endl;
    cout<<"Front: "<<i.Front()<<endl;
    cout<<"Rear: "<<i.Rear()<<endl;
    cout<<"Pop one from front"<<endl;
    i.Pop();
    cout<<"Front: "<<i.Front()<<endl;
    cout<<"Pop one from rear"<<endl;
    i.PopR();
    cout<<"Rear: "<<i.Rear()<<endl;
    cout<<"size: "<<i.Size()<<endl;
    return 0;
}