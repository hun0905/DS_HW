#include<iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;
template <class T>
void showlist(const T* e)
{
    for(int i = 1 ;  i < 21 ; i++)
        cout<<e[i]<<",";
    cout<<endl;
}
template <class T>
void Insert(const T& e, T *a, int i)
{
    a[0] = e;
    while(e < a[i])
    {
        a[i+1] = a[i];
        i--;
    }
    a[i+1]=e;
}
template <class T>
void InsertionSort(T*a,const int n)
{
    for(int j=2 ; j<=n ; j++){
        T temp = a[j];
        showlist(a);
        Insert(temp,a,j-1);
    }
}
template <class T>
void QuickSort(T *a, const int left, const int right)
{

    if(left<right){
        int i = left,j = right+1;
        T pivot = a[left];
        int count = 0;
        do{
            showlist(a);
            do i++;while(a[i]<pivot && i <= right);
            do j--;while(a[j]>pivot && j >= left);
            if(i<j)swap(a[i],a[j]);
        count++;
        }while(i<j);
        swap(a[left],a[j]);
        QuickSort(a,left,j-1);
        QuickSort(a,j+1,right);
    }
}
template <class T>
void Merge(T *initList, T *mergedList, const int l, const int m,const int n)
{
    int i1,i2,iResult;
    for(i1 = l,iResult = l, i2 = m+1; i1 <= m && i2 <= n; iResult++)
    {
        if(initList[i1]<=initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            mergedList[iResult] = initList[i2];
            i2++;
        }
    }
    copy(initList+i1, initList+m+1 , mergedList+iResult);
    copy(initList + i2 , initList + n + 1,mergedList+iResult);
    
}
template <class T>
void MergePass(T *initList, T *resultList, const int n, const int s)
{
    int i;
    showlist(initList);
    for(i=1; i <= n-2*s+1; i+= 2*s)
    {
        Merge(initList,resultList,i,i+s-1,i+2*s-1);
    }
    if((i+s-1)<n)Merge(initList,resultList,i,i+s-1,n);
    else copy(initList+i,initList+n+1,resultList+i);
}
template <class T>
void MergeSort(T *a, const int n)
{
    T *tempList = new T[n+1];
    for(int l = 1 ; l < n ; l*=2)
    {
        
        MergePass(a,tempList,n,l);
        l*=2;
        MergePass(tempList,a,n,l);
    }
    delete []tempList;
}
template<class T>
int ListMerge(T *a, int* link,const int start1, const int start2)
{
    int iResult=0;
    int i1,i2;
    //cout<<start1<<" "<<start2<<endl;
    for(i1 = start1,i2 = start2;i1&&i2;)
        if(a[i1] <= a[i2]){
            link[iResult] = i1;//19
            iResult = i1;i1 = link[i1];//19,0
        }
        else{
            link[iResult]= i2;
            iResult = i2;i2 = link[i2];
        }
    if(i1 == 0) link[iResult] = i2;
    else link[iResult] = i1;
    
    return link[0];
}
template<class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{
    if(left>=right)return left;
    int mid =(left+right)/2;
    
    return ListMerge(a,link,rMergeSort(a,link,left,mid),rMergeSort(a,link,mid+1,right));
}
template<class T>
void Adjust(T *a,const int root, const int n)
{
    T e = a[root];
    int j;
    for(j = 2*root;j<=n;j*=2){
        if(j<n&&a[j]<a[j+1])j++;
        if(e >= a[j])break;
        a[j/2]=a[j];
    }
    a[j/2] = e;
}
template<class T>
void HeapSort(T *a,const int n)
{
    for(int i = n/2 ; i>=1 ;i--){
        Adjust(a,i,n);
    }
    for(int i = n-1 ; i>= 1 ;i--)
    {
        showlist(a);
        swap(a[1],a[i+1]);
        Adjust(a,1,i);
    }
}
int main()
{
    srand( time(NULL));
    
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int *I = new int[21];
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  rand()%500;
    }
    cout<<"InsertionSort: "<<endl;
    InsertionSort(I,20);
    showlist(I);
    cout<<"final list"<<endl;
    showlist(I);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  rand()%500;
        
    }
    cout<<"QuickSort: "<<endl;
    QuickSort(I,1,20);
    cout<<"final list"<<endl;
    showlist(I);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  rand()%500;
    }
    cout<<"iterative merge sort: "<<endl;
    MergeSort(I,20);
    cout<<"final list"<<endl;
    showlist(I);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  rand()%500;
        cout<<I[i]<<" ";
    }
    cout<<endl;
    int *link = new int [21];
    for(int i = 1 ; i < 21 ; i++)
    {
        link[i] = 0;
    }
    rMergeSort(I,link+1,1,20);
    cout<<"recursive merge sort: "<<endl;
    int init = link[1];
    int tmp = 1;
    cout<<"link: "<<endl;
    showlist(link);
    cout<<"final list"<<endl;
    while(link[tmp])
    {
        cout<<I[link[tmp]]<<",";
        tmp = link[tmp]+1;
    }
    cout<<"\n\n";
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  rand()%500;
        cout<<I[i]<<" ";
    }
    cout<<endl;
    cout<<"HeapSort: "<<endl;
    HeapSort(I,20);
    cout<<"final list"<<endl;
    showlist(I);

    cout<<endl;
    
    float *F = new float[21];
    for(int i = 1 ; i < 21 ;i++){
        F[i] =  rand()%500/100.0;
    }
    cout<<"InsertionSort: "<<endl;
    InsertionSort(F,20);
    showlist(F);
    cout<<"final list"<<endl;
    showlist(F);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        F[i] =  rand()%500/100.0;
    }
    cout<<"QuickSort: "<<endl;
    QuickSort(F,1,20);
    cout<<"final list"<<endl;
    showlist(F);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        F[i] =  rand()%500/100.0;
    }
    cout<<"iterative merge sort: "<<endl;
    MergeSort(F,20);
    cout<<"final list"<<endl;
    showlist(F);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        F[i] =  rand()%500/100.0;
    }
    cout<<endl;
    int *link2= new int [21];
    for(int i = 1 ; i < 21 ; i++)
    {
        link2[i] = 0;
    }
    rMergeSort(F,link2+1,1,20);
    cout<<"recursive merge sort: "<<endl;
    init = link2[1];
    int tmp3 = 1;
    cout<<"link: "<<endl;
    showlist(link2);
    cout<<"final list"<<endl;
    while(link[tmp3])
    {
        cout<<F[link[tmp3]]<<",";
        tmp3 = link[tmp3]+1;
    }
    cout<<"\n\n";
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        F[i] =  rand()%500/100.0;
        
    }
    cout<<endl;
    cout<<"HeapSort: "<<endl;
    HeapSort(F,20);
    cout<<"final list"<<endl;
    showlist(F);
    cout<<endl;
    
    char *C = new char[21];
    for(int i = 1 ; i < 21 ;i++){
        C[i] =  charset[rand()%52];
    }
    cout<<"InsertionSort: "<<endl;
    InsertionSort(C,20);
    showlist(C);
    cout<<"final list"<<endl;
    showlist(C);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        C[i] =  charset[rand()%52];
    }
    cout<<"QuickSort: "<<endl;
    QuickSort(C,1,20);
    cout<<"final list"<<endl;
    showlist(C);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        I[i] =  charset[rand()%52];
    }
    cout<<"iterative merge sort: "<<endl;
    MergeSort(C,20);
    cout<<"final list"<<endl;
    showlist(C);
    cout<<endl;
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        C[i] =  charset[rand()%52];
    }
    cout<<endl;
    int *link3 = new int [21];
    for(int i = 1 ; i < 21 ; i++)
    {
        link3[i] = 0;
    }
    rMergeSort(C,link3+1,1,20);
    cout<<"recursive merge sort: "<<endl;
    init = link3[1];
    int tmp2 = 1;
    cout<<"link: "<<endl;
    showlist(link3);
    cout<<"final list"<<endl;
    while(link3[tmp2])
    {
        cout<<C[link3[tmp2]]<<",";
        tmp2 = link3[tmp2]+1;
    }
    cout<<"\n\n";
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        C[i] =  charset[rand()%52];
        
    }
    cout<<endl;
    cout<<"HeapSort: "<<endl;
    HeapSort(C,20);
    cout<<"final list"<<endl;
    showlist(C);
    cout<<endl;
    
    
    string *S = new string[21];
    
    for(int i = 1 ; i < 21 ;i++){
        S[i] = "";
        for(int j = 0 ; j < 2 + rand()%5 ; j++)
            S[i] +=  charset[rand()%52];
    }
    cout<<endl;
    cout<<"InsertionSort: "<<endl;
    InsertionSort(S,20);
    showlist(S);
    cout<<"final list"<<endl;
    showlist(S);
    cout<<endl;
    cout<<"generate another list"<<endl;
    string q[21]={"0","wjD","HyW","zfONjF","nDp","CSLS","NVRk","NxOK","dC","HvA","yIxBU","VR","DwRQK","EBUj","NiQ","mm","GKhRwX","yJ","KV","lhX","ZLamLY"};
    cout<<endl;
    cout<<"QuickSort: "<<endl;
    QuickSort(q,1,20);
    cout<<"final list"<<endl;
    showlist(q);
    cout<<endl;
    cout<<"generate another list"<<endl;
   
    for(int i = 1 ; i < 21 ;i++){
        S[i] = "";
        for(int j = 0 ; j < 2 + rand()%5 ; j++)
            S[i] +=  charset[rand()%52];
    }
    cout<<endl;
    cout<<"iterative merge sort: "<<endl;
    MergeSort(S,20);
    cout<<"final list"<<endl;
    showlist(S);
    cout<<endl;
    cout<<"generate another list"<<endl;
    
    for(int i = 1 ; i < 21 ;i++){
        S[i] = "";
        for(int j = 0 ; j < 2 + rand()%5 ; j++)
            S[i] +=  charset[rand()%52];
    }
    cout<<endl;
    int *link4 = new int [21];
    for(int i = 1 ; i < 21 ; i++)
    {
        link4[i] = 0;
    }
    rMergeSort(S,link4+1,1,20);
    cout<<"recursive merge sort: "<<endl;
    init = link4[1];
    int tmp4 = 1;
    cout<<"link: "<<endl;
    showlist(link);
    cout<<"final list"<<endl;
    while(link4[tmp4])
    {
        cout<<S[link4[tmp4]]<<",";
        tmp4 = link4[tmp4]+1;
    }
    cout<<"\n\n";

    
    cout<<"generate another list"<<endl;
    for(int i = 1 ; i < 21 ;i++){
        S[i] = "";
        for(int j = 0 ; j < 2 + rand()%5 ; j++)
            S[i] +=  charset[rand()%52];
    }
    cout<<endl;
    cout<<"HeapSort: "<<endl;
    HeapSort(S,20);
    cout<<"final list"<<endl;
    showlist(S);
    cout<<endl;
    
}