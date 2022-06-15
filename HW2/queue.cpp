#include <iostream>
using namespace std;
template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);

    bool IsEmpty() const;

    T &Front() const;

    T &Rear() const;

    void Push(const T &item);

    void Pop();

    int Size();

    int Capacity();

    T Outqueue(int i) const;

    Queue<T> Merge(Queue<T> q);

private:
    T *queue;
    int front, rear, capacity;
};
template <class T>
Queue<T>::Queue(int queueCapacity ) : capacity(queueCapacity)
{
    if (capacity < 1)
        throw "Queue capacity must be > 0";
    queue = new T[capacity];
    front = rear = 0;
}
template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear;
}
template <class T>
inline T &Queue<T>::Front() const
{
    if (IsEmpty())
        throw "Queue is empty NO front element";
    return queue[(front + 1) % capacity];
}
template <class T>
inline T &Queue<T>::Rear() const
{
    if (IsEmpty())
        throw "Queue is empty. NO rear element";
    return queue[rear];
}
template <class T>
void Queue<T>::Push(const T &x)
{
    if ((rear + 1) % capacity == front)
    {
        T *newQu = new T[2 * capacity];
        capacity*=2;
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQu);
        else
        {
            copy(queue + start, queue + capacity, newQu);
            copy(queue, queue + rear + 1, newQu + capacity - start); //一圈沒用到的加進去,rear在繞了過一圈
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        delete[] queue;
        queue = newQu;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}
template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty())
        throw "Queue is empty, cannot delete";

    front = (front + 1) % capacity;
    this->array[front].~T();
}
template <class T>
inline int Queue<T>::Size()
{
    if (rear % capacity > front % capacity)
        return rear % capacity - front % capacity;
    else
        return capacity - front % capacity + rear % capacity;
}
template <class T>
inline int Queue<T>::Capacity()
{
    return capacity;
}
template <class T>
T Queue<T>::Outqueue(int i) const
{
    return queue[i];
}
template <class T>
Queue<T> Queue<T>::Merge(Queue<T> q)
{
    if (Size() != q.Size())
        throw "The size is diffrent";
    Queue<T> result(capacity + q.capacity);
    int posa = 1, posb = 1;
    while (posa < Size()+1 && posb < q.Size()+1)
    {
        result.Push(Outqueue(( (posa + front) % capacity) ) );
        //cout<<Outqueue(( (posa + front) % capacity) )<<endl;
        result.Push(q.Outqueue(( (posb + q.front) % capacity) ));
        //cout<<q.Outqueue(( (posb + q.front) % capacity) )<<endl;
        posa++;
        posb++;
    }
    return result;
}
int main()
{
    int capacity1, capacity2;
    cout << "input capacity of queue1" << endl;
    cin >> capacity1;
    char tmp;
    Queue<char> i1(capacity1);
    cout<<"input the element of queue1"<<endl;
    for(int i = 0 ; i < capacity1 ; i++)
    {
        cin>>tmp;
        i1.Push(tmp);
    }
    cout << "input capacity of queue2" << endl;
    cin >> capacity2;
    Queue<char> i2(capacity2);
    cout<<"input the element of queue2"<<endl;
    for(int i = 0 ; i < capacity2 ; i++)
    {
        cin>>tmp;
        i2.Push(tmp);
    }
    Queue<char>i3(capacity2*2);
    i3 = i1.Merge(i2);
    cout<<"the result of merge ";
    for(int i = 0 ; i < capacity2*2 ; i++)  
        cout<<i3.Outqueue(i)<<" ";
    cout<<endl;
}